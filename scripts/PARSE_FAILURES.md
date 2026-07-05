# Real-repo parse failures

Corpus: 90 `.q` files under `test/real/`. Target <2% bad; current regression floor <68%.
Result: **44.44%** bad (40/90) — PASS (floor). Gap to target: 42%.

- ERROR-node files: 40
- Timeouts (parser hang): 0
- Crashes (non-zero exit): 0

## ERROR-node files

- `test/real/cookbook/bloomberg/bpipe.q`
- `test/real/cookbook/bloomberg/fh_callbacks.q`
- `test/real/cookbook/dataloader/gencsv.q`
- `test/real/cookbook/dataloader/loader.q`
- `test/real/cookbook/pubsub/subscriber.q`
- `test/real/cookbook/r/rserve/demo.q`
- `test/real/cookbook/r/rserver/examples/e4.q`
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
- `test/real/kdb/e/c.q`
- `test/real/kdb/e/d0.q`
- `test/real/kdb/e/tpcd.q`
- `test/real/kdb/taq/adj.q`
- `test/real/kdb/taq/daily.q`
- `test/real/kdb/taq/tq.q`
- `test/real/kdb/tick/chainedtick.q`
- `test/real/kdb/tick/ssl.q`
- `test/real/kdb/tq.q`
- `test/real/kdb/tree.q`
- `test/real/kdb/utils/csvguess.q`
- `test/real/kdb/utils/csvutil.q`
- `test/real/kdb/utils/dbmaint.q`
- `test/real/reQ/examples/aoc.q`
- `test/real/reQ/examples/github.q`
- `test/real/reQ/req/auth.q`
- `test/real/reQ/req/cookie.q`
- `test/real/reQ/req/doh_google.q`
- `test/real/reQ/req/ext/os.q`
- `test/real/reQ/req/json.q`
- `test/real/reQ/req/req.q`
- `test/real/reQ/req/url.q`

## Timeouts

- (none)

## Crashes

- (none)
