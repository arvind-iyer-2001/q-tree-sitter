# Real-repo parse failures

Corpus: 90 `.q` files under `test/real/`. Target <2% bad; current regression floor <68%.
Result: **15.56%** bad (14/90) — PASS (floor). Gap to target: 14%.

- ERROR-node files: 14
- Timeouts (parser hang): 0
- Crashes (non-zero exit): 0

## ERROR-node files

- `test/real/cookbook/bloomberg/fh_callbacks.q`
- `test/real/cookbook/tutorial/smartmeterfunctions.q`
- `test/real/cookbook/tutorial/tutorial.q`
- `test/real/kdb/e/tpcd.q`
- `test/real/kdb/taq/adj.q`
- `test/real/kdb/taq/bucket.q`
- `test/real/kdb/taq/daily.q`
- `test/real/kdb/tick/c.q`
- `test/real/kdb/tick/ssl.q`
- `test/real/kdb/utils/csvguess.q`
- `test/real/kdb/utils/csvutil.q`
- `test/real/reQ/req/cookie.q`
- `test/real/reQ/req/req.q`
- `test/real/reQ/tests/test_cookies.q`

## Timeouts

- (none)

## Crashes

- (none)
