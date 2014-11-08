"==========================================
"Highlight All Function
"==========================================
syn match cFunctions "\<[a-zA-Z_][a-zA-Z_0-9]*\>[^()]*)("me=e-2
syn match cFunctions "\<[a-zA-Z_][a-zA-Z_0-9]*\>\s*("me=e-1
hi cFunctions gui=NONE cterm=underline ctermfg=2
"=========================================
"Highlight All Math Operator
"=========================================
"C math operators
syn match cMathOperator display "[-+\*/%=]"
"C pointer operators
syn match cPointerOperator display "->\|\."
"C logical operators
syn match cLogicalOperator display "[!<>]=\="
syn match cLogicalOperator display "=="
"C bit operators
syn match cBinaryOperator display "\(&\||\|\^\|<<\|>>\)=\="
syn match cBinaryOperator display "\~"
syn match cBinaryOperatorError display"\~="
"More C logical operators - highlight in preference to binary
syn match cLogicalOperator display "&&\|||"
syn match cLogicalOperatorError display "\(&&\|||\)="

"Math Operator
hi def link cMathOperator Conditional    
"gui=NONE guifg=#FFFFFF
hi def link cPointerOperator Conditional  
"gui=NONE guifg=#FFFFFF
hi def link  cLogicalOperator Conditional  
"gui=NONE guifg=#3EFFE2
hi def link cBinaryOperator Conditional   
"gui=NONE guifg=#3EFFE2
hi def link cBinaryOperatorError Conditional 
"gui=NONE guifg=#3EFFE2
hi def link cLogicalOperator  Conditional
"gui=none guifg=#287525
hi def link cLogicalOperatorError Conditional
"gui=none guifg=#78A525 guibg=#C00000

"=========================================
"My Own DataType
"=========================================
"syn keyword cType int char float shor
