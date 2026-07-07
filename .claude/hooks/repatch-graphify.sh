#!/bin/bash
# PostToolUse hook: if a Bash command (re)installed or upgraded graphify,
# re-apply q-support wiring — upgrades overwrite site-packages and silently
# drop the .q extractor. Reads the hook JSON on stdin.
set -u
INPUT=$(cat)
CMD=$(printf '%s' "$INPUT" | python3 -c "import json,sys; print(json.load(sys.stdin).get('tool_input',{}).get('command',''))" 2>/dev/null)

case "$CMD" in
  *graphifyy*)
    case "$CMD" in
      *"tool install"*|*"tool upgrade"*|*"pip install"*)
        REPO_DIR=$(cd "$(dirname "$0")/../.." && pwd)
        echo "graphify install/upgrade detected — re-applying q wiring" >&2
        python3 "$REPO_DIR/tools/patch_graphify.py" >&2 || \
          echo "WARNING: patch_graphify.py failed — run it manually" >&2
        ;;
    esac
    ;;
esac
exit 0
