def test_language_loads():
    import tree_sitter, tree_sitter_q
    lang = tree_sitter.Language(tree_sitter_q.language())
    parser = tree_sitter.Parser(lang)
    tree = parser.parse(b"f:{x+y}")
    assert tree.root_node.type == "source_file"
    assert "ERROR" not in str(tree.root_node)

def test_extracts_assignment_lambda():
    import tree_sitter, tree_sitter_q
    p = tree_sitter.Parser(tree_sitter.Language(tree_sitter_q.language()))
    root = p.parse(b"add:{[a;b]a+b}").root_node
    asn = root.children[0]
    assert asn.type == "assignment"
    assert asn.child_by_field_name("right").type == "lambda"
