# Real-repo parse failures

Corpus: 90 `.q` files under `test/real/`. Target <2% bad; current regression floor <68%.
Result: **8.89%** bad (8/90) — PASS (floor). Gap to target: 7%.

- ERROR-node files: 8
- Timeouts (parser hang): 0
- Crashes (non-zero exit): 0

## ERROR-node files

- `test/real/cookbook/tutorial/smartmeterfunctions.q`
- `test/real/kdb/e/tpcd.q`
- `test/real/kdb/taq/adj.q`
- `test/real/kdb/taq/bucket.q`
- `test/real/kdb/taq/daily.q`
- `test/real/kdb/tick/c.q`
- `test/real/kdb/tick/ssl.q`
- `test/real/reQ/req/cookie.q`

## Timeouts

- (none)

## Crashes

- (none)
