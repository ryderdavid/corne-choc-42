#!/usr/bin/env python3
"""
Fat Finger Typo Generator for QMK Autocorrect
Generates transposition, deletion, extra letter, and replacement typos from a word list.
"""

import sys
import argparse
from collections import defaultdict
from multiprocessing import Pool, cpu_count
from typing import Optional
from wordfreq import word_frequency, top_n_list
from english_words import get_english_words_set


# region config
class Config:
    """Configuration for typo generation."""
    def __init__(self, args):
        self.freq_ratio = args.freq_ratio
        self.max_word_length = args.max_word_length
        self.min_word_length = args.min_word_length
        self.min_typo_length = args.min_typo_length
        self.typo_freq_threshold = args.typo_freq_threshold
        self.verbose = args.verbose
        self.jobs = args.jobs
        self.output = args.output


# region validation helpers
def is_valid_qmk_word(word: str) -> bool:
    """
    Check if word contains only characters QMK autocorrect can handle.

    QMK autocorrect only supports:
    - Lowercase letters (a-z)
    - Apostrophes (')

    It does NOT support:
    - Periods, hyphens, numbers, or other punctuation
    """
    for char in word:
        if not (char.isalpha() or char == "'"):
            return False
    return True


# region typo gen
def generate_transpositions(word: str) -> list[str]:
    """Generate all possible adjacent character transpositions."""
    typos = []
    for i in range(len(word) - 1):
        typo = word[:i] + word[i+1] + word[i] + word[i+2:]
        typos.append(typo)
    return typos


def generate_deletions(word: str) -> list[str]:
    """Generate single character deletions (only for words with 4+ characters)."""
    if len(word) < 4:
        return []

    typos = []
    for i in range(len(word)):
        typo = word[:i] + word[i+1:]
        typos.append(typo)
    return typos


def generate_extra_letters(word: str, extra_map: dict[str, str]) -> list[str]:
    """Generate typos by inserting extra letters before and after each character."""
    if not extra_map:
        return []

    typos = []
    for i, char in enumerate(word):
        if char in extra_map:
            for extra in extra_map[char]:
                # Extra after
                typos.append(word[:i+1] + extra + word[i+1:])
                # Extra before
                typos.append(word[:i] + extra + word[i:])

    return typos


def generate_replacements(word: str, extra_map: dict[str, str]) -> list[str]:
    """Generate typos by replacing characters with adjacent keys."""
    if not extra_map:
        return []

    typos = []
    for i, char in enumerate(word):
        if char in extra_map:
            for replacement in extra_map[char]:
                typos.append(word[:i] + replacement + word[i+1:])

    return typos


def generate_all_typos(word: str, extra_letters_map: Optional[dict[str, str]] = None) -> list[str]:
    """Generate all types of typos for a word."""
    typos = generate_transpositions(word) + generate_deletions(word)

    if extra_letters_map:
        typos.extend(generate_extra_letters(word, extra_letters_map))
        typos.extend(generate_replacements(word, extra_letters_map))

    return typos


# region val+filt
def is_substring_of_any(typo: str, word_set: set[str]) -> bool:
    """Check if typo is a substring of any word in word_set."""
    for word in word_set:
        if typo in word and typo != word:
            return True
    return False


def would_trigger_at_start(typo: str, validation_set: set[str]) -> bool:
    """Check if :typo would falsely trigger (typo appears as prefix)."""
    for word in validation_set:
        if word.startswith(typo) and word != typo:
            return True
    return False


def would_trigger_at_end(typo: str, validation_set: set[str]) -> bool:
    """Check if typo: would falsely trigger (typo appears as suffix)."""
    for word in validation_set:
        if word.endswith(typo) and word != typo:
            return True
    return False


def would_trigger_as_substring(typo: str, validation_set: set[str]) -> bool:
    """Check if typo appears as substring anywhere in validation words."""
    for word in validation_set:
        if typo in word and word != typo:
            return True
    return False


def determine_boundaries(
    typo: str,
    validation_set: set[str],
    source_words: set[str],
) -> Optional[str]:
    """
    Determine what boundaries (if any) are needed for a typo.

    Returns:
        - typo without boundaries if safe
        - typo with boundaries (:typo, typo:, :typo:) if needed
        - None if typo should be skipped
    """
    is_substring_source = is_substring_of_any(typo, source_words)
    is_substring_validation = would_trigger_as_substring(typo, validation_set)

    if not is_substring_source and not is_substring_validation:
        # Safe without boundaries
        return typo

    # Need boundaries - determine which
    appears_as_prefix = would_trigger_at_start(typo, validation_set)
    appears_as_suffix = would_trigger_at_end(typo, validation_set)

    if not appears_as_prefix and not appears_as_suffix:
        return f":{typo}:"
    if appears_as_suffix and not appears_as_prefix:
        return f":{typo}"
    if appears_as_prefix and not appears_as_suffix:
        return f"{typo}:"
    return f":{typo}:"


def process_word(
    word: str,
    validation_set: set[str],
    source_words: set[str],
    typo_freq_threshold: float,
    extra_letters_map: Optional[dict[str, str]],
) -> list[tuple[str, str]]:
    """
    Process a single word and generate all valid corrections.

    Returns list of (typo, word) tuples.
    """
    corrections = []
    typos = generate_all_typos(word, extra_letters_map)

    for typo in typos:
        # Skip if typo is the word itself
        if typo == word:
            continue

        # Skip if typo is a valid word
        if typo in validation_set:
            continue

        # Skip if typo has significant frequency (likely a real word)
        if typo_freq_threshold > 0.0:
            typo_freq = word_frequency(typo, 'en')
            if typo_freq >= typo_freq_threshold:
                continue

        # Determine boundaries
        typo_with_boundaries = determine_boundaries(typo, validation_set, source_words)
        if typo_with_boundaries:
            corrections.append((typo_with_boundaries, word))

    return corrections


# region exclusions

class ExclusionMatcher:
    """Handles all exclusion logic including wildcards and patterns."""

    def __init__(self, exclusion_set: set[str]):
        self.exclusions = exclusion_set
        self.wildcards = [e for e in exclusion_set if '*' in e and ' -> ' not in e]
        self.patterns = [e for e in exclusion_set if ' -> ' in e]
        self.exact = [e for e in exclusion_set if '*' not in e and ' -> ' not in e]

    def should_exclude(self, correction: str) -> bool:
        """Check if a correction should be excluded."""
        if ' -> ' not in correction:
            return False

        typo_part, word_part = correction.split(' -> ', 1)
        clean_typo = typo_part.strip(':')

        # Check exact matches
        if correction in self.exact:
            return True
        if clean_typo in self.exact:
            return True
        if typo_part in self.exact:
            return True
        if word_part in self.exact:
            return True

        # Check wildcards
        for wildcard in self.wildcards:
            if self._matches_wildcard(word_part, wildcard):
                return True

        # Check patterns
        for pattern in self.patterns:
            if self._matches_pattern(typo_part, word_part, pattern):
                return True

        return False

    def _matches_wildcard(self, word: str, wildcard: str) -> bool:
        """Check if word matches wildcard pattern."""
        if wildcard.startswith('*') and wildcard.endswith('*'):
            return wildcard.strip('*') in word
        elif wildcard.startswith('*'):
            return word.endswith(wildcard[1:])
        elif wildcard.endswith('*'):
            return word.startswith(wildcard[:-1])
        return False

    def _matches_pattern(self, typo_part: str, word_part: str, pattern: str) -> bool:
        """Check if correction matches exclusion pattern."""
        excl_typo, excl_word = pattern.split(' -> ', 1)
        clean_typo = typo_part.strip(':')

        # Suffix pattern: "in: -> ing"
        if excl_typo.endswith(':') and not excl_typo.startswith(':'):
            pattern_typo = excl_typo[:-1]
            if clean_typo.endswith(pattern_typo) and word_part.endswith(excl_word):
                return True

        # Prefix pattern: ":ah -> ha"
        if excl_typo.startswith(':') and not excl_typo.endswith(':'):
            pattern_typo = excl_typo[1:]
            if clean_typo.startswith(pattern_typo) and word_part.startswith(excl_word):
                return True

        # Full pattern: ":word: -> correction"
        if excl_typo.startswith(':') and excl_typo.endswith(':'):
            pattern_typo = excl_typo.strip(':')
            if clean_typo == pattern_typo and word_part == excl_word:
                return True

        return False


# region pattern check

def generalize_patterns(
    corrections: list[str],
    validation_set: set[str],
    min_typo_length: int,
) -> list[str]:
    """
    Generalize corrections into patterns when possible.

    QMK allows patterns like "in: -> ing" to match multiple typos.
    """
    # Group corrections by their pattern
    suffix_patterns = defaultdict(list)  # "in:" -> ["goin:", "doin:", ...]
    prefix_patterns = defaultdict(list)  # ":teh" -> [":teh", ...]

    for correction in corrections:
        if ' -> ' not in correction:
            continue

        typo, word = correction.split(' -> ', 1)

        # Check for suffix pattern (typo:)
        if typo.endswith(':') and not typo.startswith(':'):
            pattern = typo
            suffix_patterns[pattern].append(word)

        # Check for prefix pattern (:typo)
        if typo.startswith(':') and not typo.endswith(':'):
            pattern = typo
            prefix_patterns[pattern].append(word)

    # Generate patterns (need at least 2 occurrences)
    patterns = []

    for pattern, words in suffix_patterns.items():
        if len(words) < 2:
            continue

        # Check pattern length
        if len(pattern) < min_typo_length:
            continue

        # Find common suffix in words
        if len(set(words)) == 1:
            # All map to same word
            correction = words[0]
            pattern_correction = f"{pattern} -> {correction}"

            # Validate pattern won't cause false triggers
            clean_pattern = pattern.strip(':')
            if not would_trigger_at_end(clean_pattern, validation_set):
                patterns.append(pattern_correction)

    for pattern, words in prefix_patterns.items():
        if len(words) < 2:
            continue

        if len(pattern) < min_typo_length:
            continue

        if len(set(words)) == 1:
            correction = words[0]
            pattern_correction = f"{pattern} -> {correction}"

            clean_pattern = pattern.strip(':')
            if not would_trigger_at_start(clean_pattern, validation_set):
                patterns.append(pattern_correction)

    return patterns


# region collisions

def resolve_collisions(
    typo_map: dict[str, list[str]],
    freq_ratio: float,
    min_typo_length: int,
    user_included_words: set[str],
    exclusion_matcher: ExclusionMatcher,
) -> tuple[list[str], list, list]:
    """
    Resolve collisions where multiple words generate the same typo.

    Returns (corrections, skipped_collisions, skipped_short_typos).
    """
    final_corrections = []
    skipped_collisions = []
    skipped_short_typos = []

    for typo, possible_words in typo_map.items():
        # Deduplicate
        possible_words = list(set(possible_words))

        if len(possible_words) == 1:
            word = possible_words[0]
            clean_typo = typo.strip(':')

            # Special case: 2-char user words get wrapped
            if word in user_included_words and len(word) == 2:
                correction = f":{clean_typo}: -> {word}"
                if not exclusion_matcher.should_exclude(correction):
                    final_corrections.append(correction)
            elif len(clean_typo) < min_typo_length:
                skipped_short_typos.append((typo, word, len(clean_typo)))
            else:
                correction = f"{typo} -> {word}"
                if not exclusion_matcher.should_exclude(correction):
                    final_corrections.append(correction)
        else:
            # Collision - resolve by frequency
            word_freqs = [(w, word_frequency(w, 'en')) for w in possible_words]
            word_freqs.sort(key=lambda x: x[1], reverse=True)

            most_common = word_freqs[0]
            second_most = word_freqs[1] if len(word_freqs) > 1 else (None, 0)

            ratio = most_common[1] / second_most[1] if second_most[1] > 0 else float('inf')

            if ratio > freq_ratio:
                word = most_common[0]
                clean_typo = typo.strip(':')

                if word in user_included_words and len(word) == 2:
                    correction = f":{clean_typo}: -> {word}"
                    if not exclusion_matcher.should_exclude(correction):
                        final_corrections.append(correction)
                elif len(clean_typo) < min_typo_length:
                    skipped_short_typos.append((typo, word, len(clean_typo)))
                else:
                    correction = f"{typo} -> {word}"
                    if not exclusion_matcher.should_exclude(correction):
                        final_corrections.append(correction)
            else:
                skipped_collisions.append((typo, possible_words, ratio))

    return final_corrections, skipped_collisions, skipped_short_typos


def remove_substring_conflicts(corrections: list[str], verbose: bool) -> list[str]:
    """Remove corrections where one typo is a substring of another."""
    typo_to_correction = {}
    for correction in corrections:
        if ' -> ' in correction:
            typo, _ = correction.split(' -> ', 1)
            typo_to_correction[typo] = correction

    typos_to_remove = set()
    typo_list = list(typo_to_correction.keys())

    for i, typo1 in enumerate(typo_list):
        if typo1 in typos_to_remove:
            continue
        for typo2 in typo_list[i+1:]:
            if typo2 in typos_to_remove:
                continue

            clean_typo1 = typo1.strip(':')
            clean_typo2 = typo2.strip(':')

            if clean_typo1 in clean_typo2:
                typos_to_remove.add(typo2)
            elif clean_typo2 in clean_typo1:
                typos_to_remove.add(typo1)

    if typos_to_remove and verbose:
        print(f"# Removed {len(typos_to_remove)} typos due to substring conflicts", file=sys.stderr)

    return [
        typo_to_correction[t] for t in typo_to_correction if t not in typos_to_remove  # pylint: disable=consider-using-dict-items
    ]


# region file io

def load_validation_dictionary(exclude_words: list[str], verbose: bool) -> set[str]:
    """Load the English words validation dictionary."""
    if verbose:
        print("Loading English words dictionary...", file=sys.stderr)

    validation_set = get_english_words_set(['web2', 'gcide'], lower=True, alpha=True)

    # Remove excluded words
    for word in exclude_words:
        validation_set.discard(word.lower())

    if verbose:
        print(f"Loaded {len(validation_set)} words for validation", file=sys.stderr)

    return validation_set


def load_exclusions(filepath: Optional[str], verbose: bool) -> set[str]:
    """Load exclusion patterns from file."""
    if not filepath:
        return set()

    exclusions = set()
    with open(filepath, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue
            exclusions.add(line.lower())

    if verbose:
        print(f"Loaded {len(exclusions)} exclusions from {filepath}", file=sys.stderr)

    return exclusions


def load_adjacent_letters(filepath: Optional[str], verbose: bool) -> dict[str, str]:
    """Load adjacent letters mapping from file."""
    if not filepath:
        return {}

    adjacent_map = {}
    with open(filepath, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip()
            if not line or line.startswith('#'):
                continue

            if '->' in line:
                char, adjacent = line.split('->', 1)
                char = char.strip().lower()
                adjacent = adjacent.strip().replace(' ', '')

                if len(char) == 1:
                    adjacent_map[char] = adjacent

    if verbose:
        print(f"Loaded {len(adjacent_map)} extra letter mappings", file=sys.stderr)

    return adjacent_map


def load_word_list(filepath: Optional[str], verbose: bool = False) -> list[str]:
    """Load words from file, filtering out words with invalid characters."""
    if not filepath:
        return []

    words = []
    invalid_count = 0
    with open(filepath, 'r', encoding='utf-8') as f:
        for line in f:
            line = line.strip().lower()
            if line and not line.startswith('#'):
                if is_valid_qmk_word(line):
                    words.append(line)
                else:
                    invalid_count += 1

    if verbose and invalid_count > 0:
        print(f"Skipped {invalid_count} words from {filepath} with invalid characters", file=sys.stderr)

    return words


def load_source_words(args, verbose: bool) -> list[str]:
    """Load and filter source words from all sources."""
    input_words = []

    # Get from top-n
    if args.top_n:
        if verbose:
            print(
                f"Pulling top {args.top_n} words from wordfreq that meet criteria...",
                file=sys.stderr,
            )

        candidate_words = top_n_list('en', args.top_n * 10)

        for word in candidate_words:
            if len(word) < args.min_word_length:
                continue
            if args.max_word_length and len(word) > args.max_word_length:
                continue

            input_words.append(word)

            if len(input_words) >= args.top_n:
                break

        if verbose:
            print(f"Selected {len(input_words)} words from top-n", file=sys.stderr)

    # Read from stdin if no other sources
    if not args.top_n and not args.include:
        if sys.stdin.isatty():
            print("Enter words (one per line, Ctrl+D to finish):", file=sys.stderr)
        for line in sys.stdin:
            line = line.strip().lower()
            if line:
                input_words.append(line)

    # Apply filters
    filtered_words = []
    invalid_char_count = 0
    for word in input_words:
        if len(word) < args.min_word_length:
            continue
        if args.max_word_length and len(word) > args.max_word_length:
            continue
        if not is_valid_qmk_word(word):
            invalid_char_count += 1
            continue
        filtered_words.append(word)

    if verbose:
        if len(filtered_words) < len(input_words):
            filtered_count = len(input_words) - len(filtered_words)
            print(f"Filtered {filtered_count} words by length constraints", file=sys.stderr)
        if invalid_char_count > 0:
            print(f"Filtered {invalid_char_count} words with invalid characters (periods, hyphens, etc.)", file=sys.stderr)

    return filtered_words


# region multiprocessing

# Global state for workers
_VALIDATION_SET = None
_SOURCE_WORDS_SET = None
_TYPO_FREQ_THRESHOLD = 0.0
_EXTRA_LETTERS_MAP = None


def _init_worker(validation_set, source_words_set, typo_freq_threshold, extra_letters_map):
    """Initialize worker process."""
    # pylint: disable=global-statement
    global _VALIDATION_SET, _SOURCE_WORDS_SET, _TYPO_FREQ_THRESHOLD, _EXTRA_LETTERS_MAP
    _VALIDATION_SET = validation_set
    _SOURCE_WORDS_SET = source_words_set
    _TYPO_FREQ_THRESHOLD = typo_freq_threshold
    _EXTRA_LETTERS_MAP = extra_letters_map


def _process_word_worker(word):
    """Worker function for multiprocessing."""
    return (
        word,
        process_word(
            word, _VALIDATION_SET, _SOURCE_WORDS_SET, _TYPO_FREQ_THRESHOLD, _EXTRA_LETTERS_MAP,
        ),
    )


# region main pipeline

def run_pipeline(args):
    """Main processing pipeline."""
    config = Config(args)

    # Load dictionaries and mappings
    validation_set = load_validation_dictionary(args.exclude, config.verbose)
    exclusions = load_exclusions(args.exclude_file, config.verbose)
    exclusion_matcher = ExclusionMatcher(exclusions)
    adjacent_letters_map = load_adjacent_letters(args.adjacent_letters, config.verbose)

    # Load source words
    user_included_words = load_word_list(args.include, config.verbose)
    if config.verbose and user_included_words:
        print(f"Loaded {len(user_included_words)} words from include file", file=sys.stderr)

    user_included_words_set = set(user_included_words)
    source_words = load_source_words(args, config.verbose)
    source_words.extend(user_included_words)

    if config.verbose and user_included_words:
        print(
            f"Included {len(user_included_words)} words from include file (bypassed filters)",
            file=sys.stderr,
        )

    if config.verbose:
        print(f"\nProcessing {len(source_words)} words...\n", file=sys.stderr)

    source_words_set = set(source_words)

    # Process words
    typo_map = defaultdict(list)

    if config.jobs > 1:
        if config.verbose:
            print(
                f"Processing {len(source_words)} words using {config.jobs} workers...",
                file=sys.stderr,
            )

        with Pool(
            processes=config.jobs, initializer=_init_worker,
            initargs=(
                validation_set,
                source_words_set,
                config.typo_freq_threshold,
                adjacent_letters_map,
            ),
        ) as pool:
            results = pool.map(_process_word_worker, source_words)

        for word, corrections in results:
            for typo, correction in corrections:
                typo_map[typo].append(correction)
    else:
        for word in source_words:
            corrections = process_word(word, validation_set, source_words_set,
                                     config.typo_freq_threshold, adjacent_letters_map)
            for typo, correction in corrections:
                typo_map[typo].append(correction)

    # Resolve collisions
    final_corrections, skipped_collisions, skipped_short = resolve_collisions(
        typo_map, config.freq_ratio, config.min_typo_length,
        user_included_words_set, exclusion_matcher
    )

    # Statistics
    if config.verbose:
        print(
            f"# Generated {len(final_corrections)} corrections (before pattern generalization)",
            file=sys.stderr,
        )
        if skipped_short:
            print(
                f"# Skipped {len(skipped_short)} typos shorter than {config.min_typo_length} characters",
                file=sys.stderr,
            )
        if skipped_collisions:
            print(f"# Skipped {len(skipped_collisions)} ambiguous collisions:", file=sys.stderr)
            for typo, words, ratio in skipped_collisions[:5]:
                print(f"#   {typo}: {words} (ratio: {ratio:.2f})", file=sys.stderr)

    # Generalize patterns
    patterns = generalize_patterns(final_corrections, validation_set, config.min_typo_length)
    final_corrections.extend(patterns)

    if config.verbose:
        print(f"# After pattern generalization: {len(final_corrections)} entries", file=sys.stderr)

    # Remove substring conflicts
    final_corrections = remove_substring_conflicts(final_corrections, config.verbose)

    # Sort output
    def sort_key(correction):
        if ' -> ' in correction:
            typo, word = correction.split(' -> ', 1)
            return (word, typo)
        return (correction, '')

    output_lines = sorted(final_corrections, key=sort_key)

    # Write output
    if config.output:
        with open(config.output, 'w', encoding='utf-8') as f:
            for line in output_lines:
                f.write(line + '\n')
        if config.verbose:
            print(f"\nWrote {len(output_lines)} corrections to {config.output}", file=sys.stderr)
    else:
        for line in output_lines:
            print(line)


# region cli

def main():
    """Main entry point."""
    parser = argparse.ArgumentParser(
        description='Generate QMK autocorrect dictionary from common typos',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog="""
Examples:
  # Get top 100 most common words
  %(prog)s --top-n 100 -o autocorrect.txt

  # Top 100 + your custom words (bypasses length filters)
  %(prog)s --top-n 100 --include mywords.txt -o autocorrect.txt

  # With extra letters for fat-finger errors
  %(prog)s --top-n 1000 --adjacent-letters adjacents.txt -o autocorrect.txt

  # With exclusions and custom settings
  %(prog)s --top-n 1000 --exclude-file exclusions.txt --max-length 8 -o autocorrect.txt
        """
    )

    # Output
    parser.add_argument('-o', '--output', type=str,
                       help='Output file for corrections. If not specified, writes to stdout')
    parser.add_argument('--top-n', type=int,
                       help='Pull top N most common English words that meet criteria (from wordfreq)')

    # Word lists
    parser.add_argument('--include', type=str,
                       help='File with additional words to include (one per line, always bypasses length filters)')
    parser.add_argument('--exclude', action='append', default=[],
                       help='Words to exclude from validation (treat as typos) (can be specified multiple times)')
    parser.add_argument('--exclude-file', type=str,
                       help='File with exclusions: typos, patterns, and wildcards to skip (one per line, # for comments)')
    parser.add_argument('--adjacent-letters', type=str,
                       help='File mapping keys to possible extra letters (e.g., "b -> nvgh")')

    # Parameters
    parser.add_argument('--freq-ratio', type=float, default=10.0,
                       help='Minimum frequency ratio for collision resolution (default: 10.0)')
    parser.add_argument('--max-word-length', type=int, default=10,
                       help='Maximum word length to process (default: 10)')
    parser.add_argument('--min-word-length', type=int, default=3,
                       help='Minimum source word length (default: 3)')
    parser.add_argument('--min-typo-length', type=int, default=5,
                       help='Minimum typo length to include in output (default: 5)')
    parser.add_argument('--typo-freq-threshold', type=float, default=0.0,
                       help='Skip typos with wordfreq frequency above this (0.0 = disabled, try 1e-7)')

    # Flags
    parser.add_argument('-v', '--verbose', action='store_true',
                       help='Verbose output (show stats and skipped collisions)')
    parser.add_argument('-j', '--jobs', type=int, default=cpu_count(),
                       help=f'Number of parallel workers (default: {cpu_count()})')

    args = parser.parse_args()

    run_pipeline(args)


if __name__ == "__main__":
    main()
