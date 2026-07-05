# Real-repo parse failures

Corpus: 90 `.q` files under `test/real/`. Target <2% bad; current regression floor <68%.
Result: **6.67%** bad (6/90) — PASS (floor). Gap to target: 5%.

- ERROR-node files: 6
- Timeouts (parser hang): 0
- Crashes (non-zero exit): 0

## ERROR-node files

- `test/real/cookbook/tutorial/smartmeterfunctions.q`
- `test/real/kdb/taq/adj.q`
- `test/real/kdb/taq/bucket.q`
- `test/real/kdb/taq/daily.q`
- `test/real/kdb/tick/c.q`
- `test/real/kdb/tick/ssl.q`

## Timeouts

- (none)

## Crashes

- (none)
