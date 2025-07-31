#!/bin/bash

# Basic Regular Expression Meta Characters:
# 1) . (dot) matches any single character.
# 2) Character classes []: allow to match any specific character within []
# 	a. ^ (negate) within [] is used to ignore the match.
# 	b. Ranges can also be specified like [a-z] or [0-9]
# 	c. Combine multiple ranges like [a-z0-9]
# 	d. Named character classes, mainly for portability across languages.
# 		[[:upper:]], lower, alpha, alnum, digit, punct, cntrl
# 3) Anchors: Allows to match the beginning and the end of a line
# 	a. ^ match the beginning of the line
# 	b. $ match the end of the line
# 4) Repetitions:
# 	a. * matches zero or more occurences of the immediate preceding character.
# 	b. {} specify extract occurences
# 		{n} matches exactly n occurences of the immediate preceding character.
# 		{n,m} matches at least n times and at most m times.
# 		{,m} matches at most M times.
# 5) Subexpressions: allows us to treat the text as a single character.
# 	a. We use (pattern)
# 6) Back-references: allow us to match the pattern that was made in earlier sub-expressions.
# 	a. We use \n like \1 (first subexpression), \2 (second subexpressions.)
#
#
#
#
# Extended Regular Expression Metacharacters:
# 7. | (alternation): allows to match one or another subexpression.
# 8. + (repetition): allows to match one or more occurence of the immediately preceding character. Same as writing {1,}
# 9. ? (optional): allows to match zero or one occurence of the immediate preceding character.
