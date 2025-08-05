program CaseTest;

type
    sizes = (small, medium, large);

var
    i, j, even, odd, prime : integer;
    ch, str : char;
    size : sizes;

begin {CASE statements}
    i := 3; ch := 'b' ;
    size := medium;
    even := -990; odd := -999; prime := 0;

    case i of
        1       : j := i;
        -8      : j := 8*i;
        5, 7, 4 : j := 574*i;
    end;

    case i+1 of
        1       : j := i;
        -8      : j := 8*i;
        5, 7, 4 : j := 574*i;
    end;

    case ch of
        'c', 'b'    : str := 'p';
        'a'         : str := 'q'
    end;

    case size of
        small   : str := 's';
        medium  : str := 'm';
        large   : str := 'l';
    end;

    case i of
        2   : prime := i;
        -4, -2, 0, 4, 6, 8, 10, 12  : even := i;
        -3, -1, 1, 3, 5, 7, 9, 11   : case i of 
                                            -3, -1, 1, 9    : odd := i;
                                            2, 3, 5, 7, 11  : prime := i;
                                      end;
    end;
    
    { COMPILER ERROR WHEN CASE IN A FOR LOOP }
    {
    for i := -5 to 15 do begin
        case i of
            2   : prime := i;
            -4, -2, 0, 4, 6, 8, 10, 12  : even := i;
            -3, -1, 1, 3, 5, 7, 9, 11   : case i of 
                                                -3, -1, 1, 9    : odd := i;
                                                2, 3, 5, 7, 11  : prime := i;
                                          end;
        end;
    end;
    }

    { TRY A CASE IN A WHILE LOOP : THIS WORKS FINE}
    while i < 10 do begin
        case i of
            2   : prime := i;
            -4, -2, 0, 4, 6, 8, 10, 12  : even := i;
            -3, -1, 1, 3, 5, 7, 9, 11   : case i of 
                                                -3, -1, 1, 9    : odd := i;
                                                2, 3, 5, 7, 11  : prime := i;
                                          end;
        end;
    end;

    { TRY A CASE IN A IF STATEMENT : THIS WORKS FINE}
    if i < 10 then
        case i of
            2   : prime := i;
            -4, -2, 0, 4, 6, 8, 10, 12  : even := i;
            -3, -1, 1, 3, 5, 7, 9, 11   : case i of 
                                                -3, -1, 1, 9    : odd := i;
                                                2, 3, 5, 7, 11  : prime := i;
                                          end;
        end;

    { TRY A CASE IN A REPEAT STATEMENT : THIS WORKS FINE}
    REPEAT
        case i of
            2   : prime := i;
            -4, -2, 0, 4, 6, 8, 10, 12  : even := i;
            -3, -1, 1, 3, 5, 7, 9, 11   : case i of 
                                                -3, -1, 1, 9    : odd := i;
                                                2, 3, 5, 7, 11  : prime := i;
                                          end;
        end;
    UNTIL i < 10
end.

