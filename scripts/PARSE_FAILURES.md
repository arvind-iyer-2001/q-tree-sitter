# Real-repo parse failures

Corpus: 90 `.q` files under `test/real/`. Target <2% bad; current regression floor <68%.
Result: **3.33%** bad (3/90) — PASS (floor). Gap to target: 1%.

- ERROR-node files: 3
- Timeouts (parser hang): 0
- Crashes (non-zero exit): 0

## ERROR-node files

- `test/real/kdb/taq/adj.q`
- `test/real/kdb/taq/daily.q`
- `test/real/kdb/tick/ssl.q`

## Timeouts

- (none)

## Crashes

- (none)
