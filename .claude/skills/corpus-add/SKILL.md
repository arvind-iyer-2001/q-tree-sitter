---
name: corpus-add
description: Add a q/kdb+ repository to the parser's real-world test corpus and surface what the grammar can't parse yet. Use when expanding coverage — "add <repo> to the corpus", "test the parser against <path>".
---

# /corpus-add <github-url | local path>

Grow `test/real/` and measure. The corpus doubles as the parse-rate
regression gate, so additions RAISE the bar permanently.

## 1. Fetch

- GitHub URL → `git clone --depth 1 <url> /tmp/corpus-add/<name>`
- Local path → use as-is
- PROPRIETARY code: ASK before copying into this repo, even though
  `test/real/` is gitignored — gitignore is not an access-control boundary.
  Offer the alternative: run the measurement in-place without copying
  (parse_rate.py takes any directory).

## 2. Install

```bash
cp -r <src> test/real/<name>/
# corpus is gitignored; graphify needs the negation file — verify it exists:
cat test/real/.graphifyignore   # must contain !**
```

## 3. Baseline measurement

```bash
python3 scripts/parse_rate.py test/real/          # overall rate vs 3% floor
python3 scripts/categorize_errors.py              # bucket the new failures
```
If the floor now fails: the new repo exposed real grammar gaps. That is the
POINT — do not remove the repo to get green.

## 4. Report

Present per-bucket counts for the NEW files only (diff PARSE_FAILURES.md
against git HEAD's copy). For each bucket give one representative line of
real source. Rank by file count.

## 5. Fix loop

For each bucket, top-down, invoke `/grammar-fix <representative construct>`.
After each fix, re-run parse_rate — buckets often collapse together.
Stop when the floor passes again; file remaining rare buckets as handoff
open items rather than forcing risky grammar changes.

## 6. Wrap up

- `scripts/parse_rate.py` FLOOR: tighten if the new steady-state rate allows
  (floor should sit just above the known-failure count).
- Note the new corpus source + license in `test/real/<name>/SOURCE.txt`
  (upstream URL + commit) so a fresh machine can re-fetch — the corpus
  itself does not travel with the repo.
- Update HANDOFF.md open items if buckets were deferred.
