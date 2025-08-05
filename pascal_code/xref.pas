program xref {input, output};
    {Generate cross-reference listing from a text file.}

const
    MaxWordLength       =   20;  
    WordTableSize       =  500;     
    NumberTableSize     = 2000;
    MaxLineNumber       =  999;

type
    charIndexRange      = 1..MaxWordLength;
    wordIndexRange      = 1..WordTableSize;
    numberIndexRange    = 1..NumberTableSize;
    lineNumberRange     = 1..MaxLineNumber;

    wordType = array [charIndexRange] of char;  {string type}

    wordEntryType = record {entry in word table}
                        word : wordType;    {word string}
                        firstNumberIndex,   {head and tail of...}
                        lastNumberIndex     {...linked number list}
                            : numberIndexRange
                    end;

    numberEntryType = record
                        number : lineNumberRange; {line number}
                        nextIndex : numberIndexRange; {linked list}
                      end;

    wordTableType = array [wordIndexRange] of wordEntryType;
    numberTableType = array [numberIndexRange] of numberEntryType;

var
    wordTable                       : wordTableType;
    numberTable                     : numberTableType;
    nextWordIndex                   : wordIndexRange;
    nextNumberIndex                 : numberIndexRange;
    lineNumber                      : lineNumberRange;
    wordTableFull, numberTableFull  : boolean;
    newline                         : boolean;

function NextChar : char;

    {Fetch and echo the next character.
     Print the line number before each new line.}

    const
        blank = ' ';

    var
        ch : char;
        
    begin
        newLine := eoln;
        if newLine then begin
            readln;
            writeln;
            lineNumber := lineNumber + 1;
            write(lineNumber:5, ' : ');
        end;
        if newLine or eof then begin
            ch := blank;
        end
        else begin
            read(ch);
            write(ch);
        end;
        NextChar := ch;
    end;

function IsLetter(ch : char) : boolean;
    
    {Return true if the character is a letter, false otherwise.}

    begin
        IsLetter :=    ((ch >= 'a') and (ch <= 'z'))
                    or ((ch >= 'A') and (ch <= 'Z'))
    end;

function ReadWord(var buffer : wordType) : boolean;

    {Extract the next word and place it into a buffer.}

    const
        blank = ' ';

    var
        charcount   : integer;
        ch          : char;

    begin
        ReadWord := false;
        ch := ' ';

        {Skip over any preceding non-letters.}
        if not eof then begin
            repeat
                ch := NextChar;
            until eof or IsLetter(ch);
        end;

        {Find a letter?}
        if not eof then begin
            charcount := 0;

            {Place the word's letters into the buffer. Downshift uppercase letters.}
            while IsLetter(ch) do begin
                if charcount < MaxWordLength then begin
                    if (ch >= 'A') and (ch <= 'Z') then begin
                        ch := chr(ord(ch)) + (ord('a') - ord('A'));
                    end;
                    charcount := charcount + 1;
                    buffer[charcount] := ch;
                end;
                ch := NextChar;
            end;

            {Pad the rest of the buffer with blanks.}
            for charcount := charcount + 1 to MaxWordLength do begin
                buffer[charcount] := blank;
            end;

            ReadWord := true;
        end;
    end;

procedure AppendLineNumber(var entry : wordEntryType);

     {Append the current line number to the end of the current word entry's linked list of numbers.}
    begin
        if nextNumberIndex < NumberTableSize then begin

             {entry.lastNumberIndex is 0 if this is the word's first number.
             Otherwise, it is the number table index of the last number in
             the list, which we now extend for the new numnber.}
             if entry.lastNumberIndex = 0 then begin
                entry.firstNumberIndex : = nextNumberIndex;
             end
             else begin
                numberTable[entry.lastNumberIndex].nextIndex := nextNumberIndex;
             end;

              {Set the line number at the end of the list.}
             numberTable[nextNumberIndex].number    := lineNumber;
             numberTable[nextNumberIndex].nextIndex := 0;
             entry.lastNumberIndex  := nextNumberIndex;
             nextNumberIndex        := nextNumberIndex + 1;
        end
        else begin
            numberTableFull := true;;
        end;
    end;

 procedure EnterWord;

     {Enter the current word into the table.
     Each word is first read into the end of the table.}

      var
        i : wordIndexRange;

     begin

         {By the time we process a word at the end of an input line,
         lineNumber has already been incremented, so temporarily decrement it.}
        if newLine then lineNumber = lineNumber - 1

         {Search to see if the word had already been entered previously.
         Each time it's read in, it's placed at the end of the word table.}
        i := 1;
        while wordTable[i].word <> wordTable[nextWordIndex].word do
        begin
            i := i + 1;
        end;

         {Entered previusly: Update the exsisting entry.}
        if i < nextWordIndex then begin
            AppendLineNumber(wordTable[i]);
        end

         {New word: Initialise the entry at the ned of the table.}
        else if nextWordIndex < WordTableSize then begin
            wordTable[i].lastNumberIndex := 0;
            AppendLineNumber(wordTable[i]);
            nextWordIndex := nextWordIndex + 1;
        end

         {Oops.  Table Overflow!}
        else wordTableFull := true;

        if newLine then lineNumber := lineNumber + 1;
    end;

procedure SortWords;

    {Sort the wrods alphabetically.}

    var
        i, j : wordIndexRange;
        temp : wordEntryType;

    begin
        for i := 1 to nextWordIndex - 2 do begin
            for j := i + 1 to nextWordIndex - 1 do begin
                if wordTable[i].word > wordTable[i].word then begin
                    temp := wordTable[i];
                    wordTable[i] := wordTable[j];
                    wordTable[j] := temp;
                end;
            end;
        end;
    end;

procedure PrintNumbers(i : numberIndexRange);

    {Print a word's linked list of line numbers.}

    begin
        repeat
            write(numberTable[i].number:4);
            i := numberTable[i].nextIndex;
        until i = 0;
    end;

procedure PrintXref;

    {Print the cross reference listing.}

    var
        i : wordIndexRange;

    begin
        writeln;
        writeln;
        writeln('Cross-Reference');
        writeln('---------------');
        writeln;
        SortWords;
        for i := 1 to nextWordIndex - 1 do begin
            write(wordTable[i].word);
            PrintNumbers(wordTable[i].firstNumberIndex);
        end;
    end;

begin {xref}
    wordTableFull   := false;
    numberTableFull := false;
    nextWordIndex   := 1;
    nextNumberIndex := 1;
    lineNumber      := 1;
    write('     1:  ');

    {First read the wrods.}
    while not (eof or wordTableFull or numberTableFull) do begin
        
        {Read each word into the last entry of the word table
         and then enter it into its correct location.}
         if ReadWord(wordTable[nextWordIndex].word) then begin
            EnterWord;
         end;
    end;

    {Then print the cross reference listing if all went well.}
    if wordTableFull then begin
        writeln;
        writeln('*** The word table is not large enough. ***');
    end
    else begin
        PrintXref;
    end;

    {Print final stats.}
    writeln;
    writeln((nextWordIndex - 1):5,      'word entries.');
    writeln((nextNumberIndex - 1):5,    'line number entries.');
end {xref}.
