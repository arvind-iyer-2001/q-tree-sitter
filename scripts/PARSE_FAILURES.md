# Real-repo parse failures

Corpus: 90 `.q` files under `test/real/`. Target <2% bad; current regression floor <72%.
Result: **68.89%** bad (62/90) — PASS (floor). Gap to target: 67%.

- ERROR-node files: 62
- Timeouts (parser hang): 0
- Crashes (non-zero exit): 0

## ERROR-node files

- `test/real/cookbook/bloomberg/bpipe.q`
- `test/real/cookbook/bloomberg/fh_callbacks.q`
- `test/real/cookbook/dataloader/gencsv.q`
- `test/real/cookbook/dataloader/loader.q`
- `test/real/cookbook/pubsub/subscriber.q`
- `test/real/cookbook/r/rserve/demo.q`
- `test/real/cookbook/r/rserver/rinit.q`
- `test/real/cookbook/r/rserver/rtest.q`
- `test/real/cookbook/start/buildhdb.q`
- `test/real/cookbook/start/tick/cx.q`
- `test/real/cookbook/start/tick/feed.q`
- `test/real/cookbook/tutorial/buildsmartmeterdb.q`
- `test/real/cookbook/tutorial/smartmeterfunctions.q`
- `test/real/cookbook/tutorial/tutorial.q`
- `test/real/cookbook/tutorial/ui/smartmeterui.q`
- `test/real/cookbook/yahoo.q`
- `test/real/kdb/bell.q`
- `test/real/kdb/c/bcp.q`
- `test/real/kdb/c/feed/ssl.q`
- `test/real/kdb/comb.q`
- `test/real/kdb/e/c.q`
- `test/real/kdb/e/d0.q`
- `test/real/kdb/e/dmm.q`
- `test/real/kdb/e/huff.q`
- `test/real/kdb/e/mserve.q`
- `test/real/kdb/greplin.q`
- `test/real/kdb/holiday.q`
- `test/real/kdb/sp.q`
- `test/real/kdb/sparse.q`
- `test/real/kdb/stat.q`
- `test/real/kdb/taq/adj.q`
- `test/real/kdb/taq/daily.q`
- `test/real/kdb/taq/taq.q`
- `test/real/kdb/taq/tq.q`
- `test/real/kdb/tick/c.q`
- `test/real/kdb/tick/chainedr.q`
- `test/real/kdb/tick/chainedtick.q`
- `test/real/kdb/tick/ssl.q`
- `test/real/kdb/tick/test.q`
- `test/real/kdb/tq.q`
- `test/real/kdb/tree.q`
- `test/real/kdb/utils/csvguess.q`
- `test/real/kdb/utils/csvutil.q`
- `test/real/kdb/utils/dbmaint.q`
- `test/real/reQ/examples/aoc.q`
- `test/real/reQ/examples/github.q`
- `test/real/reQ/examples/util.q`
- `test/real/reQ/lint.q`
- `test/real/reQ/req/auth.q`
- `test/real/reQ/req/b64.q`
- `test/real/reQ/req/cookie.q`
- `test/real/reQ/req/doh_google.q`
- `test/real/reQ/req/ext/os.q`
- `test/real/reQ/req/json.q`
- `test/real/reQ/req/multipart.q`
- `test/real/reQ/req/req.q`
- `test/real/reQ/req/status.q`
- `test/real/reQ/req/timeout.q`
- `test/real/reQ/req/url.q`
- `test/real/reQ/tests/test_b64.q`
- `test/real/reQ/tests/test_cookies.q`
- `test/real/reQ/tests/test_requests.q`

## Timeouts

- (none)

## Crashes

- (none)
