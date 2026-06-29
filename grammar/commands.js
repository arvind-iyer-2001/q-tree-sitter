// Grammar rules for system/backslash commands.
//
// DESIGN DECISION (for T10 and T12):
//   namespace_directive is FOLDED into system_command.
//
// Rationale: The external scanner (T2) emits the entire `\...` line as
// $._system_command_tok. The T2 scanner is still a stub (always returns false)
// in this worktree, so we define an inline token _sys_cmd_line that matches
// the same text pattern. When T2's real scanner is wired in, it will emit
// $._system_command_tok; the inline token becomes dead code (external token wins).
//
// Structurally distinguishing `\d .ns` as a separate `namespace_directive`
// node would require the scanner NOT to include `\d` inside a single opaque
// token — which is incompatible with the T2 contract (scanner emits the WHOLE
// line). Therefore `\d .util` is represented as:
//
//   (source_file (system_command) ...)
//
// The downstream extractor (T12) inspects the token text (startsWith('\d'))
// to detect namespace switches. T10 is informed: `namespace_directive` is NOT
// a separate node; it is removed. grammar.js _statement has a W1-commands note.
//
// Covers: \l \d \c \p \P \x \w \\ \ts \t \a \b \v \B \C \cd \e \E \f \g
//         \o \r \s \S \T \u \v \w \W \x \z \1 \2 \_ and OS-escape commands.

module.exports = {
  // Inline token matching a whole backslash-command line (stub for T2 scanner).
  // Matches \ optionally followed by any non-newline characters including args.
  // When T2's scanner emits $._system_command_tok, that external token will
  // override this inline rule (external tokens take priority in tree-sitter).
  _sys_cmd_line: $ => token(/\\[^\n]*/),

  // system_command: the single node type for ALL backslash commands.
  // Field 'command' gives the full raw text: leading \ + command letter(s) + args.
  // \l init.q   => (system_command)  — load file
  // \d .util    => (system_command)  — namespace switch (T12 detects via text)
  // \ts expr    => (system_command)  — time+space
  // \\          => (system_command)  — quit
  // \c 25 80    => (system_command)  — console size
  // \p 5001     => (system_command)  — port
  // \t 100      => (system_command)  — timer
  // \x .z.ph    => (system_command)  — expunge callback
  // \w          => (system_command)  — memory usage
  // \a          => (system_command)  — list tables
  // \b          => (system_command)  — list views
  // \v          => (system_command)  — list variables
  // \P 7        => (system_command)  — display precision
  system_command: $ => field('command', $._sys_cmd_line),
};
