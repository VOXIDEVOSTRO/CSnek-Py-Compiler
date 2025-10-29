# Rules checkbox

## Module and entry points
- [x] TreeParseModule
- [ ] TreeParseInteractive
- [x] TreeParseExpression
- [ ] TreeParseFunctionType
- [ ] TreeParseTypeIgnoreList            # type_ignores in Module
- [ ] TreeParseTypeIgnore                # single type ignore

## High-level statement dispatch
- [ ] TreeParseStatmentList              # top-level stmt* sequence
- [x] TreeParseStatment                  # statement dispatcher
- [ ] TreeParseSimpleStatment            # one line, semicolon separated
- [ ] TreeParseSmallStatment             # single simple stmt
- [ ] TreeParseCompoundStatment          # if/while/for/with/try/def/class/match
- [ ] TreeParseSuite                     # indented suite or single-line

## Simple statements
- [ ] TreeParseExprStmt
- [ ] TreeParseAssign
- [ ] TreeParseAugAssign
- [ ] TreeParseAnnAssign
- [ ] TreeParseReturn
- [ ] TreeParseRaise
- [ ] TreeParseAssert
- [ ] TreeParsePass
- [ ] TreeParseBreak
- [ ] TreeParseContinue
- [ ] TreeParseImport
- [ ] TreeParseImportFrom
- [ ] TreeParseGlobal
- [ ] TreeParseNonlocal
- [ ] TreeParseDelete

## Compound statements (bodies use TreeParseSuite/TreeParseBlock)
- [ ] TreeParseIf
- [ ] TreeParseWhile
- [ ] TreeParseFor
- [ ] TreeParseAsyncFor
- [ ] TreeParseWith
- [ ] TreeParseAsyncWith
- [ ] TreeParseTry                       # try: except*: else?: finally?
- [ ] TreeParseTryExceptHandlers         # except handlers group
- [ ] TreeParseExceptHandler             # single except handler
- [ ] TreeParseFunctionDef
- [ ] TreeParseAsyncFunctionDef
- [ ] TreeParseClassDef
- [ ] TreeParseMatch                     # Python 3.10+

## Function and class details
- [ ] TreeParseDecorators                # @decorator list
- [ ] TreeParseParameters                # (arguments)
- [ ] TreeParseArguments                 # ast.arguments
- [ ] TreeParseArg                       # ast.arg
- [ ] TreeParseDefaultsAndAnnotations    # defaults, kw_defaults, annotations
- [ ] TreeParseClassBases                # class base list
- [ ] TreeParseClassKeywords             # class keyword args
- [ ] TreeParseClassBody                 # suite

## With, imports, aliasing
- [ ] TreeParseWithItems                 # with-item list
- [ ] TreeParseWithItem                  # single with-item (as target?)
- [ ] TreeParseAliasList                 # import alias list
- [ ] TreeParseAlias                     # single alias
- [ ] TreeParseDottedName                # module/qualname in import from

## Expressions (dispatcher and precedence)
- [ ] TreeParseExpr                      # full expression entry
- [ ] TreeParseTest                      # conditional/ifexp entry
- [ ] TreeParseOrTest                    # or
- [ ] TreeParseAndTest                   # and
- [ ] TreeParseNotTest                   # not
- [ ] TreeParseComparison                # < > == != is in chains
- [ ] TreeParseExprBitOr                 # |
- [ ] TreeParseExprBitXor                # ^
- [ ] TreeParseExprBitAnd                # &
- [ ] TreeParseShiftExpr                 # << >>
- [ ] TreeParseArithExpr                 # + -
- [ ] TreeParseTerm                      # * @ / // %
- [ ] TreeParseFactor                    # + - ~ unary
- [ ] TreeParsePower                     # **, await
- [ ] TreeParseAtomExpr                  # trailer chain (calls, subscripts, attrs)
- [ ] TreeParseAtom                      # literals, names, containers, lambdas

## Expression nodes (payload construction)
- [ ] TreeParseBoolOp                    # or/and
- [ ] TreeParseBinOp                     # + - * @ / // % | ^ & << >>
- [ ] TreeParseUnaryOp                   # + - ~
- [ ] TreeParseCompare                   # chained comparisons
- [ ] TreeParseCall                      # func(args, kwargs)
- [ ] TreeParseAttribute                 # obj.attr
- [ ] TreeParseSubscript                 # obj[index/slice]
- [ ] TreeParseSlice                     # lower:upper:step
- [ ] TreeParseStarred                   # *expr in list/tuple unpack
- [ ] TreeParseLambda                    # lambda
- [ ] TreeParseIfExp                     # a if cond else b
- [ ] TreeParseAwait                     # await expr
- [ ] TreeParseYield                     # yield expr?
- [ ] TreeParseYieldFrom                 # yield from expr
- [ ] TreeParseName                      # identifiers

## Literals and constants
- [ ] TreeParseConstant                  # umbrella dispatcher
- [ ] TreeParseIntegerConstant
- [ ] TreeParseFloatConstant
- [ ] TreeParseImaginaryConstant         # complex literal parts
- [ ] TreeParseStringConstant            # non-f format strings
- [ ] TreeParseBytesConstant
- [ ] TreeParseBooleanConstant           # True/False
- [ ] TreeParseNoneConstant              # None
- [ ] TreeParseEllipsisConstant          # ...
- [ ] TreeParseJoinedStr                 # f-string container
- [ ] TreeParseFormattedValue            # f-string interpolation

## Containers
- [ ] TreeParseList                      # [elements]
- [ ] TreeParseTuple                     # (elements) or bare tuple
- [ ] TreeParseDict                      # {key: value, ...}
- [ ] TreeParseSet                       # {elem, ...}
- [ ] TreeParseComprehension             # for-if generators (shared)
- [ ] TreeParseListComp                  # [elt for ...]
- [ ] TreeParseSetComp                   # {elt for ...}
- [ ] TreeParseDictComp                  # {key: value for ...}
- [ ] TreeParseGeneratorExp              # (elt for ...)

## Call arguments and keywords
- [ ] TreeParseArgList                   # positional + keyword + *args/**kwargs
- [ ] TreeParseKeyword                   # key=value
- [ ] TreeParsePositionalArgs
- [ ] TreeParseVarArg                    # *args in call
- [ ] TreeParseKwVarArg                  # **kwargs in call

## Pattern matching (PEP 634+)
- [ ] TreeParseMatchSubject              # subject expression
- [ ] TreeParseMatchCaseList             # case*
- [ ] TreeParseMatchCase                 # case pattern [if guard]: block
- [ ] TreeParsePattern                   # dispatcher for patterns
- [ ] TreeParseMatchValue
- [ ] TreeParseMatchSingleton            # True/False/None
- [ ] TreeParseMatchSequence             # [pats] / (pats)
- [ ] TreeParseMatchMapping              # {key: pat, ...}
- [ ] TreeParseMatchClass                # Class(pats, kw=pats)
- [ ] TreeParseMatchStar                 # *name
- [ ] TreeParseMatchAs                   # pat as name
- [ ] TreeParseMatchOr                   # pat | pat
- [ ] TreeParsePatternGuard              # if guard

## Blocks and suites
- [x] TreeParseBlock                     # your generic block node (stmt* array)
- [ ] TreeParseIndentedSuite             # colon + NEWLINE + INDENT … DEDENT
- [ ] TreeParseOneLineSuite              # colon + small_stmt

## Soft keywords and context sensitive tokens
- [ ] TreeParseSoftKeywordMatch          # match only in statement positions
- [ ] TreeParseSoftKeywordCase           # case only in match
- [ ] TreeParseAsyncKeyword              # async in def/for/with contexts

## Helpers and utilities
- [ ] TreeParseDecorator                 # single @decorator
- [ ] TreeParseColonBody                 # ":" followed by suite
- [ ] TreeParseCommaSeparated            # generic comma list helper
- [ ] TreeParseParenList                 # "(" elements ")"
- [ ] TreeParseBracketList               # "[" elements "]"
- [ ] TreeParseBraceList                 # "{" elements "}"
- [ ] TreeParseAssignTargets             # multiple targets (a, b = ...)
- [ ] TreeParseAnnTarget                 # annotated target
- [ ] TreeParseWalrusTarget              # target for := (if supported)
- [ ] TreeParseFStringParts              # lexer-assisted f-string parts

## Operator tags (used inside BinOp/UnaryOp/Compare, not standalone)
- [ ] TreeParseOperatorTag               # Add/Sub/Mult/MatMult/Div/Mod/Pow/LShift/RShift/BitOr/BitXor/BitAnd/FloorDiv
- [ ] TreeParseUnaryOperatorTag          # Invert/Not/UAdd/USub
- [ ] TreeParseComparisonOperatorTag     # Eq/NotEq/Lt/LtE/Gt/GtE/Is/IsNot/In/NotIn