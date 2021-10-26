# 2 Julia の言語機能
## 2.1 Julia の基本
### 2.1.1 変数
- 宣言と代入
    - `x = 1`
- 変数の直前の数字がかけられる
    - `2x + 1 # 3`
- 変数名にユニコードが使える
    - `θ = pi /4 # 0.7853981633974483`
    - `sin(θ ) # 0.7071067811865475`

### 2.1.2 プリミティブ型
#### 型の調べ方
- `typeof(1) # Int32`

#### プリミティブ型
- Int{8,16,32,64,128}
- UInt{8,16,32,64,128}
- Bool
- Float{16,32,64}
- Int, UInt -> システムのディフォルトのビット長のエイリアス
    - `Sys.WORD_SIZE # 32`
    - `Int # Int32`

```julia
julia> for T in [Int8,Int16,Int32,Int64,Int128,UInt8,UInt16,UInt32,UInt64,UInt128]
           println("$(lpad(T,7)): [$(typemin(T)),$(typemax(T))]")
       end
   Int8: [-128,127]
  Int16: [-32768,32767]
  Int32: [-2147483648,2147483647]
  Int64: [-9223372036854775808,9223372036854775807]
 Int128: [-170141183460469231731687303715884105728,170141183460469231731687303715884105727]
  UInt8: [0,255]
 UInt16: [0,65535]
 UInt32: [0,4294967295]
 UInt64: [0,18446744073709551615]
UInt128: [0,340282366920938463463374607431768211455]
```

#### 16進数表現
- `0x1 # 0x01`
- `typeof(0x01) # 1, b000 0001 UInt8`
- `typeof(0x123) # 291, b000 0001 0010 0011 UInt16`
- `typeof(0x1234567) # 19088743, b0000 0001 0010 0011 0100 0101 0110 0111 UInt32`
- `typeof(0x123456789abcdef) # UInt64`

#### 浮動小数点
- `typeof(1.0) # Float64`
- Float32 型を指定するときは, `0.5f0` のようにサフィックスをつける
    - `typeof(0.5f0) # Float32`
- 予約語
    - 無限: Inf{16, 32, 64}
    - -無限: -Inf{16, 32, 64}
    - Nan系: NaN{16, 32, 64}

### 2.1.3 任意制度演算
- `BigInt` 型
- `BigFloat` 型

```julia
# 書籍の例のように BigInt 型にならないですね...
julia> x = 123567890123456789012345678901234567890
123567890123456789012345678901234567890

julia> x * x
16709914794736288363445475719704024132

julia> typeof(ans)
Int128
```

```julia
# https://doc.julialang.org から
julia> x = typemax(UInt128)
0xffffffffffffffffffffffffffffffff

julia> big(x)
340282366920938463463374607431768211455

julia> typeof(x)
UInt128

julia> typeof(big(x))
BigInt
```

- "BigInts can also be input as integer literals when they are too big for other built-in integer types. Note that as there is
no unsigned arbitrary-precision integer type in Base (BigInt is sufficient in most cases), hexadecimal, octal and binary literals can be used (in
addition to decimal literals)."

### 2.1.4 定数の宣言

```julia
julia> const y = 1.0
1.0

julia> y = 1
ERROR: invalid redefinition of constant y
```

#### 最初から定義済みの定数
```
julia> pi
π  = 3.1415926535897...

julia> VERSION
v"1.6.2"
```

```
# 定義されている定数を未使用前であれば好きに定義できる
julia> pi = 3
3

# However, if you try to redefine a built-in constant or function already in use, Julia will give you an error:

julia> pi
π = 3.1415926535897...

julia> pi = 3
ERROR: cannot assign a value to variable MathConstants.pi from module Main

julia> sqrt(100)
10.0

julia> sqrt = 4
ERROR: cannot assign a value to variable Base.sqrt from module Main
```

### 2.1.5 基本的な演算子
|Expression|      Name                     | Description                            |
|----------|-------------------------------|----------------------------------------|
|+x        | unary plus                    | the identity operation                 |
|-x        | unary minus                   | maps values to their additive inverses |
|x + y     | binary plus                   | performs addition                      |
|x - y     | binary minus                  | performs subtraction                   |
|x * y     | times                         | performs multiplication                |
|x / y     | divide                        | performs division                      |
|x ÷ y    | integer divide                | x / y, truncated to an integer         |
|x \ y     | inverse divide                | equivalent to y / x                    |
|x ^ y     | power                         | raises x to the yth power              |
|x % y     | remainder                     | equivalent to rem(x,y)                 |
|!x        | negation                      |                                        |
|x && y    | short-circuiting and          |                                        |
|x \|\| y    | short-circuiting or           |                                        |
|~x        | bitwise not                   |                                        |
|x & y     | bitwise and                   |                                        |
|x \| y     | bitwise or                    |                                        |
|x ⊻ y     | bitwise xor (exclusive or)    |                                        |
|x >>> y   | logical shift right           |                                        |
|x >> y    | arithmetic shift right        |                                        |
|x << y    | logical/arithmetic shift left |                                        |
|==        | equality                      |                                        |
|!=, ≠    | inequality                    |                                        |
|<         | less than                     |                                        |
|<=, ≤    | less than or equal to         |                                        |
|>         | greater than                  |                                        |
|>=, ≥    | greater than or equal to      |                                        |

### 2.1.6 更新演算子
- `+=, -=, *=, /=, \=, ÷=, %=` など

```
julia> x = 1;

julia> x += 1
2
```

### 複素数
- `im` が虚数単位


```
julia> 1 + 2im
1 + 2im

julia> (1 + 2im) * (2 - 3im)
8 + 1im

julia> real(1 + 2im)
1

julia> imag(1 + 2im)
2

julia> conj(1 + 2im)
1 - 2im

julia> abs(1 + 2im)
2.23606797749979
```


### 2.1.8 文字列
- `String` 型
    - Unicode 文字列
    - UTF-8
- `string[idx]` で１始まり
    - `string[x以上:y以下]` という閉区間指定

```
julia> s = "Hello Julia"
"Hello Julia"

julia> s[1]
'H': ASCII/Unicode U+0048 (category Lu: Letter, uppercase)

julia> typeof(s[1])
Char

julia> s[end]
'a': ASCII/Unicode U+0061 (category Ll: Letter, lowercase)

julia> s[1:5]
"Hello"
```

#### 文字列の連結など

```
julia> h = "Hello";

julia> j = "Julia";

julia> string(h, " ", j)
"Hello Julia"

julia> h * " " * j
"Hello Julia"

julia> "$h #j"
"Hello #j"

julia> "$h $j"
"Hello Julia"
```

#### クォート
- ダブルクォートは `String` 型, 式展開可能
- バッククォートは `Cmd` 型, 式展開可能
- シングルクォートはエラー
- 生の文字列リテラルはどう出すのか

```
julia> "1 + 2 = $(1 + 2)"
"1 + 2 = 3"

julia> `1 + 2 = $(1 + 2)`
`1 + 2 = 3`

julia> '1 + 2 = $(1 + 2)'
ERROR: syntax: character literal contains multiple characters
Stacktrace:
 [1] top-level scope
   @ none:1

julia> typeof(`1 + 2 = $(1 + 2)`)
Cmd

julia> typeof("1 + 2 = $(1 + 2)")
String

julia> typeof('1 + 2 = $(1 + 2)')
ERROR: syntax: character literal contains multiple characters
Stacktrace:
 [1] top-level scope
   @ none:1

```

### 2.1.9 Unicode 文字列
- マルチバイト文字も操作できる
    - UTF-8 のような, 可変多バイト文字の扱いに注意
    - `nextiind()` 関数で次の文字のインデックスを取得できる
- 文字列などのインデックス指定に `end` キーワードが使える
    - `end-1` は, 1 byte 前を参照

```
julia> s = "こんにちは, Julia";

julia> s[1]
'こ': Unicode U+3053 (category Lo: Letter, other)

julia> s[2]
ERROR: StringIndexError: invalid index [2], valid nearby indices [1]=>'こ', [4]=>'ん'
Stacktrace:
 [1] string_index_err(s::String, i::Int32)
   @ Base ./strings/string.jl:12
 [2] getindex_continued(s::String, i::Int32, u::UInt32)
   @ Base ./strings/string.jl:233
 [3] getindex(s::String, i::Int32)
   @ Base ./strings/string.jl:226
 [4] top-level scope
   @ REPL[35]:1

julia> s[4]
'ん': Unicode U+3093 (category Lo: Letter, other)

julia> nextind(s, 1)
4

julia> nextind(s, 4)
7

# docs.julialang.org/en/v1/manual/strings
julia> str[1:4]
"こん"

julia> str[end]
'a': ASCII/Unicode U+0061 (category Ll: Letter, lowercase)

julia> str[end-1]
'i': ASCII/Unicode U+0069 (category Ll: Letter, lowercase)

julia> str[end-2]
'l': ASCII/Unicode U+006C (category Ll: Letter, lowercase)

julia> str[end-3]
'u': ASCII/Unicode U+0075 (category Ll: Letter, lowercase)

julia> str[end-4]
'J': ASCII/Unicode U+004A (category Lu: Letter, uppercase)

```

#### 文字列を文字の配列に変換する

```
julia> chars = Vector{Char}(s)
12-element Vector{Char}:
 'こ': Unicode U+3053 (category Lo: Letter, other)
 'ん': Unicode U+3093 (category Lo: Letter, other)
 'に': Unicode U+306B (category Lo: Letter, other)
 'ち': Unicode U+3061 (category Lo: Letter, other)
 'は': Unicode U+306F (category Lo: Letter, other)
 ',': ASCII/Unicode U+002C (category Po: Punctuation, other)
 ' ': ASCII/Unicode U+0020 (category Zs: Separator, space)
 'J': ASCII/Unicode U+004A (category Lu: Letter, uppercase)
 'u': ASCII/Unicode U+0075 (category Ll: Letter, lowercase)
 'l': ASCII/Unicode U+006C (category Ll: Letter, lowercase)
 'i': ASCII/Unicode U+0069 (category Ll: Letter, lowercase)
 'a': ASCII/Unicode U+0061 (category Ll: Letter, lowercase)

```

#### Characters
- `Char` 型は
    - 32 bit 長のプリミティブ型
    - `'x'` など, いち文字
- Unicode コードポイントへ変換可能
- Go の rune 型に近いイメージ？

```
# 'x' の Unicode コードポイント
julia> c = 'x'
'x': ASCII/Unicode U+0078 (category Ll: Letter, lowercase)

julia> typeof(c)
Char

# int 型への変換
julia> c = Int('x')
120

julia> typeof(c)
Int64

julia> Char(120)
'x': ASCII/Unicode U+0078 (category Ll: Letter, lowercase)
```

### 2.1.10 文字列の関数
- 文字列を捜査する標準の関数


```
# 文字列の長さ
julia> length("Julia")
5

# 文字列の繰り返し
julia> repeat("Julia", 2)
"JuliaJulia"

# 文字列の置き換え
julia> replace("Python is the best!", "Python" => "Julia")
"Julia is the best!"

# 指定の文字で, 文字列を区切る
# CSV など？
julia> split("Julia-Lang", "-")
2-element Vector{SubString{String}}:
 "Julia"
 "Lang"

 # 指定の文字で, 開始されているか
julia> startswith("JuliaLang", "Julia")
true

# 指定の文字で, 終わっているか
julia> endswith("JuliaLang", "Lang")
true

## 指定の文字で, 文字列を連結する
julia> join(["Julia", "Lang"], "-")
"Julia-Lang"

# 文字列の検索
# findfirst は見つかった場合, 文字インデックスを返す
# 見つからなかった場合は, nothing を返す
julia> findfirst("Julia", "JuliaLang")
1:5

```


### 2.1.11 正規表現
- Julia では, PCRE (Perl Compatible Regular Expressions) という正規表現ライブラリを使える
- 文字列の前に `r` をつけることで, 正規表現を示す
    - `r"正規表現"`
- `math(正規表現型オブジェクト, "文字列")` 関数で, マッチさせる
- マッチした結果は, `RegexMatch` 型のオブジェクトが返り, 情報を持つ


```
julia> re = r"^\s*(?:#|$)"
r"^\s*(?:#|$)"

julia> typeof(re)
Regex

julia> occursin(r"^\s*(?:#|$)", "not a comment")
false

julia> occursin(r"^\s*(?:#|$)", "# a comment")
true

julia> regex = r"J.*g"
r"J.*g"

julia> typeof(regex)
Regex

julia> m = match(regex, "JuliaLang is the best.")
RegexMatch("JuliaLang")

julia> typeof(m)
RegexMatch

julia> n = match(regex, "JuliaLan is the best.")

julia> typeof(n)
Nothing

julia> m.match
"JuliaLang"

julia> m.offset
1

```


## 2.2 制御構文
### 2.2.1 条件評価
- `if, elseif, else, end` を用いて条件分岐させる


```
julia> x = 3; y = 2;

julia> if x < y
           println("x is less than y")
       elseif x > y
           println("x is greater than y")
       else
           println("x is equal to y")
       end
x is greater than y

```

- 三項演算子
    - 演算子の前にスペース必要


```
julia> x = 100;

julia> x > 100? true : false
ERROR: syntax: space required before "?" operator
Stacktrace:
 [1] top-level scope
   @ none:1

julia> x > 100 ? true : false
false
```

### 2.2.2 短絡評価
- `&&` や, `||` という演算子を用いた条件評価
    - if 文の代わりに使える
- `a && b` 
    - a ならば b という条件式
    - a と b どちらも `true` の場合のみ `true` を返す
    - a が `false` だった場合, b は評価されない
- `a || b`
    - a と b がどちらも `false` の場合のみ `false` を返す


```
# 整数 n が 0 以上のとき, エラーを返す
# a の式 n >= 0 が true のときのみ, b の式評価へ進む
julia> n = 1; n >= 0 && error("n must be negative.")
ERROR: n must be negative.
Stacktrace:
 [1] error(s::String)
   @ Base ./error.jl:33
 [2] top-level scope
   @ REPL[45]:1

# 整数 n が 0 より小さいときにエラーを返す
# a の式, n >= 0 が false のときのみ, b の式評価へ進む
julia> n = 1; n >= 0 && error("n must be non-negative.")
ERROR: n must be non-negative.
Stacktrace:
 [1] error(s::String)
   @ Base ./error.jl:33
 [2] top-level scope
   @ REPL[47]:1
```

#### && の評価

```
julia> true && true
true

julia> true && false
false

julia> false && true
false

julia> false && false
false

# 式評価
julia> returnTrue(x) = (println(x);  true)
returnTrue (generic function with 1 method)

julia> returnFalse(x) = (println(x); false)
returnFalse (generic function with 1 method)

julia> returnTrue(1) && returnTrue(2)
1
2
true

julia> returnTrue(1) && returnFalse(2)
1
2
false

# 最初の評価が false であれば, 最初の評価で止まる
julia> returnFalse(1) && returnTrue(2)
1
false

julia> returnFalse(1) && returnFalse(2)
1
false

```

#### || の評価

```
# a, b いずれかが true であれば true
julia> true || true
true

julia> true || false
true

julia> false || true
true

julia> false || false
false

# a が true であれば, 最初の式の評価で終わる
julia> returnTrue(1) || returnTrue(2)
1
true

julia> returnTrue(1) || returnFalse(2)
1
true

# a が false であれば b の式評価へ進む
julia> returnFalse(1) || returnTrue(2)
1
2
true

julia> returnFalse(1) || returnFalse(2)
1
2
false
```


#### 再帰的な階乗計算, Recursive Factorial Routine

```
julia> function factorial(n::Int)
           # n が 0 以上でないときのみ, 右の式評価へ進む
           n >= 0 || error("n must be non-negative.")
           # n が 0 であるときのみ, 右の式評価へ進む
           n == 0 && return 1
           n * factorial(n-1)
           end
factorial (generic function with 1 method)

julia> factorial(5)
120

julia> factorial(0)
1

julia> factorial(-1)
ERROR: n must be non-negative.
Stacktrace:
 [1] error(s::String)
   @ Base ./error.jl:33
 [2] factorial(n::Int64)
   @ Main ./REPL[82]:2
 [3] top-level scope
   @ REPL[85]:1

```

#### 短絡評価 を使わない場合の Boolean 演算子
- boolean のビット演算で行われる
- `|`, `&` は両辺が必ず評価される


```
# & 演算子 -> bitwiase and
julia> returnTrue(1) & returnTrue(2)
1
2
true

julia> returnTrue(1) & returnFalse(2)
1
2
false

julia> returnFalse(1) & returnTrue(2)
1
2
false

julia> returnFalse(1) & returnFalse(2)
1
2
false

# | 演算子 -> bitwise or
julia> returnTrue(1) | returnTrue(2)
1
2
true

julia> returnTrue(1) | returnFalse(2)
1
2
true

julia> returnFalse(1) | returnTrue(2)
1
2
true

julia> returnFalse(1) | returnFalse(2)
1
2
false

```


#### non-boolean 値と, 短絡評価
- boolean 値以外を最後の評価式以外に置くとエラーになる


```
julia> false || 1 && false
ERROR: TypeError: non-boolean (Int64) used in boolean context
Stacktrace:
 [1] top-level scope
   @ REPL[101]:1

julia> false || false && 1
false
```

- 最後の式評価では, いかなる式評価でも置くことができる


```
julia> true && (x = (1, 2, 3))
(1, 2, 3)

julia> false && (x = (1, 2, 3))
false

```


### 2.2.3 ループ, Rpeated Evaluation: Loops

#### while 文
- `while ... end` のブロック区内の処理を繰り返し実行できる


```
# グローバル変数として宣言
julia> i = 1
1

julia> while i <= 5
           print(i)
           # グローバル変数の変更
           # global 修飾子をつける
           global i += 1
       end
12345
```


#### for 文

```
# 1:5 は Range 型のオブジェクト
# 1 2 3 4 5 を順番に渡す
julia> typeof(1:5)
UnitRange{Int64}

julia> for i = 1:5
           print(i)
       end
12345

# 配列を使った for 文
julia> for i in [1,4,0]
           print(i)
       end
140
```


#### break, continue


```
julia> for j = 1:1000
           println(j)
           # j が 5 以上ならルーブ終了
           if j >= 5
               break
           end
       end
1
2
3
4
5

# continue
julia> for i = 1:10
           # i を 3 でわってあまりが 0 以外はスキップする
           if i % 3 != 0
               continue
           end
           println(i)
       end
3
6
9
```


#### ネストされたループを簡略化できる


```
julia> for i = 1:2
           for j = 3:4
               println((i, j))
           end
       end
(1, 3)
(1, 4)
(2, 3)
(2, 4)

julia> for i = 1:2, j = 3:4
           println((i, j))
       end
(1, 3)
(1, 4)
(2, 3)
(2, 4)

```

### 2.2.4 rty/catch/finally
- 例外処理
    - テストしたいコードを `tyr` ブロックに書く
    - 例外が発生したときにに実行される処理を `catch` ブロックに書く
    - `catch` の処理が終わった後で `finally` ブロックが実行される


```
julia> str = "Julia"
"Julia"

julia> try
           i = parse(Int, str)
           println(i)
       catch
           # ...
       end

julia> println(parse(Int, str))
ERROR: ArgumentError: invalid base 10 digit 'J' in "Julia"
Stacktrace:
 [1] tryparse_internal(#unused#::Type{Int64}, s::String, startpos::Int64, endpos::Int64, base_::Int64, raise::Bool)
   @ Base ./parse.jl:137
 [2] parse(::Type{Int64}, s::String; base::Nothing)
   @ Base ./parse.jl:241
 [3] parse(::Type{Int64}, s::String)
   @ Base ./parse.jl:241
 [4] top-level scope
   @ REPL[123]:1

```


#### ファイルの入出力

```
julia> f = open("nofile")
ERROR: SystemError: opening file "nofile": No such file or directory
Stacktrace:
 [1] systemerror(p::String, errno::Int32; extrainfo::Nothing)
   @ Base ./error.jl:168
 [2] #systemerror#62
   @ ./error.jl:167 [inlined]
 [3] systemerror
   @ ./error.jl:167 [inlined]
 [4] open(fname::String; lock::Bool, read::Nothing, write::Nothing, create::Nothing, truncate::Nothing, append::Nothing)
   @ Base ./iostream.jl:293
 [5] open(fname::String)
   @ Base ./iostream.jl:282
 [6] top-level scope
   @ REPL[124]:1

julia> try
           operate(f)
       finally
           close(f)
       end
ERROR: MethodError: no method matching close(::typeof(f))
Closest candidates are:
  close(::Union{Base.AsyncCondition, Timer}) at asyncevent.jl:136
  close(::Union{FileWatching.FileMonitor, FileWatching.FolderMonitor, FileWatching.PollingFileWatcher}) at /buildworker/worker/package_linux64/build/usr/share/julia/s
tdlib/v1.6/FileWatching/src/FileWatching.jl:304
  close(::Base.GenericIOBuffer{T}) where T at iobuffer.jl:337
  ...
Stacktrace:
 [1] top-level scope
   @ REPL[125]:4

caused by: UndefVarError: operate not defined
Stacktrace:
 [1] top-level scope
   @ REPL[125]:2

```

#### sqrt 関数を例外で場合分けする


```
julia> sqrt_second(x) = try
                  # x の２番めの要素の平方根を取る
                  sqrt(x[2])
              catch y
                  # y が DomainError であった場合
                  # DomainError, 適切なドメインの外の要素を引数にした場合
                  if isa(y, DomainError)
                      # 複素数として平方根を取る
                      sqrt(complex(x[2], 0))
                  # y が BoundsError であった場合
                  # BoundsError, 配列の長さ以外の要素にアクセスした場合
                  elseif isa(y, BoundsError)
                      sqrt(x)
                  end
              end
sqrt_second (generic function with 1 method)

julia> sqrt_second([1 4])
# 4 の平方根
2.0

julia> sqrt_second([1 -4])
# -4 の平方根
0.0 + 2.0im

julia> sqrt_second(9)
# 9 の平方根
3.0

julia> sqrt_second(-9)
ERROR: DomainError with -9.0:
sqrt will only return a complex result if called with a complex argument. Try sqrt(Complex(x)).
Stacktrace:
 [1] throw_complex_domainerror(f::Symbol, x::Float64)
   @ Base.Math ./math.jl:33
 [2] sqrt
   @ ./math.jl:582 [inlined]
 [3] sqrt
   @ ./math.jl:608 [inlined]
 [4] sqrt_second(x::Int64)
   @ Main ./REPL[137]:7
 [5] top-level scope
   @ REPL[141]:1

caused by: BoundsError
Stacktrace:
 [1] getindex
   @ ./number.jl:96 [inlined]
 [2] sqrt_second(x::Int64)
   @ Main ./REPL[137]:2
 [3] top-level scope
   @ REPL[141]:1

```


#### 独自の例外を定義する
- 構造体で宣言する

```
julia> struct MyCustomException <: Exception end

julia> struct MyUndefVarError <: Exception
           var::Symbol
       end

julia> Base.showerror(io::IO, e::MyUndefVarError) = println(io, e.var, " not defined")

```

#### 明示的なエラー文を加える
- 組み込みの例外に説明を加える
- `throw(組み込みの例外(x, "加える説明文"))` 


```
julia> f(x) = x>=0 ? exp(-x) : throw(DomainError(x, "argument must be non-negative"))
f (generic function with 1 method)

julia> f(1)
0.36787944117144233

julia> f(-1)
ERROR: DomainError with -1:
argument must be non-negative
Stacktrace:
 [1] f(x::Int64)
   @ Main ./REPL[132]:1
 [2] top-level scope
   @ REPL[134]:1

```


## 2.3 関数
- 関数とは, 引数を入力として受け取って, 何らかの結果を返すオブジェクト
- a function is an object that maps a tuple of argument values to a return value
- 最後に評価された値が自動的に戻り値となる
- pass-by-sharingと呼ばれる慣習に従ってます。
- 引数として関数に渡されるときにはその値をコピーしません。
- 引数は新しい変数として振る舞いますが、渡された値と同一のものが参照されます。
- 配列のようなミュータブルな値の変更は、呼び出し元に反映されます。

```
# function end で宣言
julia> function add(x, y)
           return x + y
       end
add (generic function with 1 method)

# 直接宣言 assignment form
julia> f(x, y) = x + y
f (generic function with 2 methods)

julia> add(2,3)
5

julia> f(2,3)
5

```

#### 引数や戻り値に型を指定
- 型はすべての引数に付与してもよいし, 一部の引数だけでも良い


```
julia> add_typed(x::Int, y::Int) = x + y;

julia> typeof(add_typed(3, 4))
Int64

julia> add_typed(x::Int8, y::Int8) = x + y;

julia> typeof(add_typed(3, 4))
Int64

julia> add_typed(x::Int8, y::Int8)::Int8 = x + y;

julia> typeof(add_typed(3, 4))
Int64

julia> function add_typed(x::Int8, y::Int8)::Int8
                  return x * y
              end;

julia> typeof(g(1,2))
Int8

```

#### 関数の戻り値を複数にする

```
julia> function sum_diff(x, y)
           x+y, x*y
       end;

julia> function sum_diff(x, y)
           x+y, x-y
       end;

julia> typeof(sum_diff(3, 4))
Tuple{Int64, Int64}

```

#### Tuple 型
- 組み込みのデータ構造
- 複数の値をまとめた型
    - 固定長のコンテナ
    - immutable であり変更できない
- `()` は空のタプル

```
julia> typeof((1, 1+1))
Tuple{Int64, Int64}

julia> typeof((1,))
Tuple{Int64}

julia> typeof((0.0, "hello", 6*7))
Tuple{Float64, String, Int64}

julia> x = (0.0, "hello", 6*7)
(0.0, "hello", 42)

julia> x[2]
"hello"

julia> typeof(())
Tuple{}

```


#### 名前付き Tuple 型
- Tuple の要素に名前をつけることができる


```
julia> x = (a=2, b=1+2)
(a = 2, b = 3)

julia> x[1]
2

julia> x.a
2

```


### 2.3.1 可変長引数, Varargs Functions
- `x...` のようにドットを３つつなげることで可変長であることを意味する
    - 引数の定義の最後の要素のみに使える
        - つまり, `bar(x..., y)` という定義はエラー
- 複数の引数をそれぞれ可変長にすることもできない
- 可変長引数に型注釈を与える
    - `g(x, y::Int...)`

```
julia> function f(x...)
           sum = 0
           println(length(x))
           # 引数の長さまでの range オブジェクト
           for i = 1:length(x)
               # 引数の Tuple にインデックスでアクセス
               sum += x[i]
           end
           sum
       end;

julia> f(3)
# 書籍の出力では 3
0.049787068367863944
# 同じセッションで, 同名の f(x) を定義していた
# julia> f(x) = x>=0 ? exp(-x) : throw(DomainError(x, "argument must be non-negative"))↲

julia> f(3)
1
3

julia> f(3,4)
7
```


#### 可変長引数と, Tuple

```
julia> bar(a, b, x...) = (a,b,x)
bar (generic function with 1 method)

# (1,2, (空のタプル))
julia> bar(1,2)
(1, 2, ())

# 3番目以降の引数は全て一つのタプルにまとめられる
julia> bar(1,2,3)
(1, 2, (3,))

julia> bar(1,2,3,4)
(1, 2, (3, 4))

julia> bar(1,2,3,4,5,7)
(1, 2, (3, 4, 5, 7))

# タプルを変数に格納
julia> x = (3,4)
(3, 4)

# タプルを格納した変数を ... を使わずに渡す
julia> bar(1,2,x)
(1, 2, ((3, 4),))

# 変数... で渡す
julia> bar(1,2,x...)
(1, 2, (3, 4))

# 要素を４つ持つタプル
julia> x = (1,2,3,4)
(1, 2, 3, 4)

julia> bar(1,2,x)
(1, 2, ((1, 2, 3, 4),))

julia> bar(x)
ERROR: MethodError: no method matching bar(::NTuple{4, Int64})
Closest candidates are:
  bar(::Any, ::Any, ::Any...) at REPL[179]:1
Stacktrace:
 [1] top-level scope
   @ REPL[189]:1

# 関数の引数で定義した, 第１, 第２引数をタプルから取り込み, 残りの要素を 可変長引数に格納する
julia> bar(x...)
(1, 2, (3, 4))

```


#### iterable オブジェクト
- いくつかの引数と可変長引数を持つ関数に, iterable オブジェクトを渡すとき 
    - 自動的にオブジェクトの先頭の要素から関数の各引数に割り当てられる


```
julia> x = [3,4]
2-element Vector{Int64}:
 3
 4

julia> bar(1,2,x...)
(1, 2, (3, 4))

julia> bar(1,2,x)
(1, 2, ([3, 4],))

julia> x = [1,2,3,4]
4-element Vector{Int64}:
 1
 2
 3
 4

julia> bar(x...)
(1, 2, (3, 4))

julia> bar(x)
ERROR: MethodError: no method matching bar(::Vector{Int64})
Closest candidates are:
  bar(::Any, ::Any, ::Any...) at REPL[179]:1
Stacktrace:
 [1] top-level scope
   @ REPL[196]:1

```


#### 可変長引数の例 rand 関数
- doc
    - https://docs.julialang.org/en/v1/stdlib/Random/#Random-generation-functions
- 書式
    - `rand([rng=GLOBAL_RNG], [S], [dims...])`
        - `rng`
            - Random Number Generator
            - 乱数生成器を指定するオプション
            - `MersenneTwister` ライブラリを通して, `MersenneTwister` オブジェクトを乱数生成に使用する
            - ほかの RNG 型は, `AbstractRNG` を継承することで追加できる
                - `RandomDevide` という RNG 型
                    - OS が提供するエントロピープール
        - `S` が示す集合からランダムな要素を取って返す
        - `S` は
            - インデックス可能なオブジェクト
            - `AbstractDict` もしくは, `AbstractSet` オブジェクト
            - 文字列
            - 型, デフォルトは `Float64` 型
                - `[0, 1)`
- `GLOBAL_RNG`
    - https://github.com/JuliaLang/julia/search?q=GLOBAL_RNG
- `Base.GLOBAL_RNG`
    - deprecated
    - https://discourse.julialang.org/t/warning-base-global-rng-is-deprecated-it-has-been-moved-to-the-standard-library-package-random/19852/2

```
# rand([dims...]) の部分の可変長引数へ渡している
julia> rand(4)
4-element Vector{Float64}:
 0.8820544785627955
 0.5393306064191477
 0.5967269773734716
 0.14746272547042816

julia> rand(4, 3)
4×3 Matrix{Float64}:
 0.651322  0.476229  0.325794
 0.27001   0.400553  0.462608
 0.707405  0.463902  0.480943
 0.97128   0.466762  0.880856

julia> rand(4, 3, 2)
4×3×2 Array{Float64, 3}:
[:, :, 1] =
 0.729712   0.968799    0.588303
 0.695648   0.571302    0.86166
 0.0757485  0.00648672  0.627555
 0.76275    0.0663761   0.316861

[:, :, 2] =
 0.964524   0.383842  0.346668
 0.0692856  0.602752  0.275058
 0.684716   0.830487  0.975866
 0.157475   0.515344  0.374874

```

### 2.3.2 オプショナル引数
- 引数にデフォルト値を設定できる

#### Date 関数の例

```
function Date(y::Int64, m::Int64=1, d::Int64=1)
    err = validargs(Date, y, m, d)
    err === nothing || throw(err)
    return Date(UTD(totaldays(y, m, d)))
end
```


```
julia> f(x, y=1) = x + y;

julia> f(3)
4

julia> f(3,4)
7

julia> using Dates

julia> Date(2000, 12, 12)
2000-12-12

julia> Date(2000)
2000-01-01
```

#### オプショナル引数の設定位置
- 末尾の引数のみ


```
julia> f(x, y=1, z=1) = x + y +z;

julia> f(x=3, y, z) = x + y + z;
ERROR: syntax: optional positional arguments must occur at end around REPL[231]:1
Stacktrace:
 [1] top-level scope
   @ REPL[231]:1
```


### 2.3.3 キーワード引数
- `function f(;引数名::型指定=デフォルト値) end`
    - `;` の後に書く
- 名前を指定して呼び出せる引数
- オプショナル引数が多いときは, キーワード引数を用いるほうが可読性が高い


```
function plot(x, y; style="solid", width=1, color="black")
    ###
end

julia> plot(1.3, 5.2, color="red")

# 型を指定して, オプショナル引数を設定
function f(;x::Int=1)
    ###
end
```


### 2.3.4 匿名関数 Anonymous Functions
- 関数名をつけずに値や, 関数の組を割り当てる
- `x -> begin end` 構文

```
julia> square = x -> begin
           x * x
       end;

julia> square = x -> x * x;

julia> square(3)
9
```


#### 一時的な関数を作成


```
julia> array = [1, 2, 3, 4, 5]
5-element Vector{Int64}:
 1
 2
 3
 4
 5

# array の各要素に対する操作
julia> map(x -> x * x, array)
5-element Vector{Int64}:
  1
  4
  9
 16
 25

julia> map(x -> x % 2 == 1, array)
5-element Vector{Bool}:
 1
 0
 1
 0
 1

julia> filter(x -> x % 2 == 1, array)
3-element Vector{Int64}:
 1
 3
 5

```


## 2.4 型
- 動的型付けであるが, 型注釈をコードに付与できる
- 多重ディスパッチによって動的にメソッド呼び出しが行われる


#### 多重ディスパッチ
- 同一の名前で引数の数や方が異なる関数を行くか定義しておき, 実行時に型に応じた適切な関数が実行される仕組み
    - C++ のオーバーロードと似ている
- 多重ディスパッチは動的に引数の型に応じた関数が呼び出される
- 単一ディスパッチは1つの型を元にメソッドを選ぶということ、多重ディスパッチはそれが複数の型に基いて選ぶということ
    - https://qiita.com/dbym4820/items/dc640bbbf4303c1a4f26#%E5%A4%9A%E9%87%8D%E3%83%87%E3%82%A3%E3%82%B9%E3%83%91%E3%83%83%E3%83%81
- 多重ディスパッチ: 動的な型情報に基づいて, 実際に呼び出すメソッドを切り変える
    - C++ の場合: https://ufcpp.net/study/csharp/sp4_multipledispatch.html
- How Julia Perfected Multiple Dispatch
    - https://towardsdatascience.com/how-julia-perfected-multiple-dispatch-16675db772c2


#### 注意点
- オブジェクト指向プログラミング言語とは異なる
    - オブジェクトに関数を所属させることはできない
    - 型の継承はできない


#### 型注釈
- 基本的に動的型付け
- 必要に応じて, 型の注釈をつけることができる
- JIT コンパイル時に, コードが最適化されて実行速度を改善する場合がある
- 多重ディスパッチが利用できる
- 利用シーン
    - コードの可読性を向上させたい場合
    - 意図的なコードの最適化を行う場合
    - 多重ディスパッチを用いる場合


#### 実行時コンパイル
- JIT コンパイル
    - LLVM



### 2.4.1 型の宣言
- `::` 演算子を使う
    - e.g., `x::Int`
- 独自の型を定義できる
    - プリミティブ型の宣言
        - `julia/base/boot.jl`
            - https://github.com/JuliaLang/julia/blob/146de38b4004e3fbd4cacc1e502fd650473cb67f/base/boot.jl#L214
        - プリミティブ型は必ず 8 bit 単位で指定する必要がある
- 型の階層構造
    - 親: supertype
        - supertype が指定されなかった場合は, `Any` 型が supertype になる
    - 子: subtype


### 2.4.2 型の階層構造
- 型同士で親子関係を構築し, 全体で型をノードとするグラフを構成する

#### 型の種類
- 具体型
    - concrete type
        - e.g., Int64, Float64 などのプリミティブ型
        - 具体型を親とする方を定義することはできない
        - 型の継承もできない
- 抽象型
    - abstract type
        - プリミティブ型の親やさらにその親となる型
        - インスタンス化してオブジェクトを生成することはできない

#### 型の例
- Abstract Float 型 -> Float{16, 32, 64} など
- Signed 型 -> Int{8, 16, 32, 64}
- Unsigned 型 -> UInt{8, 16, 32, 64}
- ![](https://i.gyazo.com/52422227289b715af5054d3b41fcf5c2.png)


#### 抽象型, abstract type
- 宣言方法
    - `<:` 演算子は親子関係を示す

```
abstract type 型名 end
abstract type 型名 <: 親の型 end
```

##### 親子関係の追跡

```
julia> supertype(Float32)
AbstractFloat

julia> supertype(AbstractFloat)
Real

julia> supertype(Real)
Number

julia> supertype(Number)
Any

julia> subtypes(Real)
# 書籍の表示は, 4-element Array{Any,1}:
# Vector 型は, Array 型の一次元の場合
4-element Vector{Any}:
 AbstractFloat
 AbstractIrrational
 Integer
 Rational

julia> subtypes(AbstractFloat)
4-element Vector{Any}:
 BigFloat
 Float16
 Float32
 Float64

julia> subtypes(Float32)
# 書籍の表示は 0-element Array{Type,1}
Type[]

```


#### Any 型
- 型グラフの最上位に位置する型
- すべての型は Any 型の子孫
- 関数の引数に型を指定しない場合は, Any 型の引数であると解釈される


### 2.4.3 Nothing 型
- Nothing 型は何もないことを表す
    - nil, null 相等?
- `nothing` という唯一のオブジェクトを持つ


```
julia> x = nothing

julia> typeof(x)
Nothing

julia> isnothing(x)
true
```

#### 関数の戻り値
- 関数の戻り値がないときは, `return nothing` と同等
- e.g., findfirst 関数


```
julia> findfirst("a", "Hello Julia!")
11:11

julia> findfirst("b", "Hello Julia!")

julia> x = findfirst("b", "Hello Julia!")

julia> typeof(x)
Nothing

```


### 2.4.4 複合型, composite types
- 複数の名前付きフィールドをまとめて扱うことのできる型
- Julia では, 関数が複合型に所属するのではなく, 型の宣言とは独立している
    - 関数が常に第一級オブジェクトとして扱われる
        - 第一級オブジェクトとは
            - 関数の引数として渡すことができる
            - 複合データ型に格納できる

```
# 複合型としての構造体
# 具体型になる -> インスタンスが生成できる
# コンストラクタは自動的に生成される
julia> struct Point
           x::Int # 型注釈
           y::Int
       end

# 複合型を引数に取るという指定のみ
julia> function distance(p::Point)
           sqrt(p.x^2 + p.y^2)
       end;

# 構造体のインスタンスの宣言
julia> p = Point(2,3)
Point(2, 3)

julia> distance(p)
3.605551275463989

# 型の調査
julia> typeof(Point)
DataType

julia> supertype(Point)
Any

julia> typeof(DataType)
DataType

julia> supertype(DataType)
Type{T}
```


#### 構造体についてすこし
- フィールドに型注釈をつけることができる
- 構造体宣言時に, コンストラクタは自動的に生成される
    - カスタムしたコンストラクタも定義できる
- フィールドには `構造体名.フィールド名` でアクセスできる
- `struct` キーワードで宣言された構造体は, 変更不可, immutable
    - `struct` で宣言されていても, フィールドの型が, 配列など変更可能なオブジェクトの場合は変更可能
- `mutable struct` キーワードで宣言すると, 変更可能, mutable

```
julia> struct Point
           x::Int
           y::Int
       end

julia> p = Point(2,3)
Point(2, 3)

julia> p.x
2

julia> p.y
3

# y=0 で初期化するコンストラクタ
julia> Point(x) = Point(x, 0);

julia> p = Point(1)
Point(1, 0)

julia> p.x
1

julia> p.x =2
ERROR: setfield! immutable struct of type Point cannot be changed
Stacktrace:
 [1] setproperty!(x::Point, f::Symbol, v::Int64)
   @ Base ./Base.jl:34
 [2] top-level scope
   @ REPL[36]:1

```

##### mutable な構造体

```
julia> mutable struct Point
           x::Int
           y::Int
       end;

julia> p = Point(3, 4)
Point(3, 4)

julia> p.x
3

julia> p.x = 1
1

```


### 2.4.5 Union 型
- 複数の型の和集合を表す型
- `Union{型名, Nothing}` 型
    - 型名で指定した型, もしくは, nothing を表す
    - 値がない状態を許す型

```
# Int または, String を表す型
julia> IntOrString = Union{Int,String}
Union{Int64, String}

julia> union_type(x::IntOrString) = x
union_type (generic function with 1 method)

julia> union_type(1)
1

julia> union_type("Julia")
"Julia"

julia> union_type(1.2)
ERROR: MethodError: no method matching union_type(::Float64)
Closest candidates are:
  union_type(::Union{Int64, String}) at REPL[5]:1
Stacktrace:
 [1] top-level scope
   @ REPL[8]:1

```


### 2.4.6 パラメトリック型
- generics やテンプレートなどの機能と似ている
- 変数に型パラメータを定義できる
- すべての `DataType` 型のインスタンスはパラメータ化できる
- e.g., `Point{T}` -> 型 T をパラメータとする Point 型
    - `Point{T}` はあらゆる型 T のテンプレートとなる

```
julia> mutable struct Point{T}
           x::T # T 型パラメータ
           y::T
       end

# 型パラメータは, `Point{T}` をインスタンス化する際に,
# Int64 や, Float64 などの具体的な型として実行する
julia> p = Point(2,3)
Point{Int64}(2, 3)

# T の型を明示できる
julia> q = Point{Int}(2,3)
Point{Int64}(2, 3)

```


#### パラメトリック型とメソッド
- `where T` を宣言時に付加する

```
julia> mutable struct Point{T}
           x::T # T 型パラメータ
           y::T
       end

# function 行に where T を付加
julia> function distance(p::Point{T}) where T
           println(T) # 型情報の出力
           sqrt(p.x^2 + p.y^2)
       end;

julia> distance(Point(2,3))
Int64
3.605551275463989
```


#### 渡される型によって動作を分ける
- 多重ディスパッチを使う -> 型によってメソッドを分ける


```
julia> function distance(p::Point{Int})
        # Int 型のときの動作
       end
distance (generic function with 2 methods)

julia> function distance(p::Point{Float64})
           # Float64 型のときの動作
       end
distance (generic function with 2 methods)

julia> function distance(p::Point)
           # それ以外のときの操作
           throw("Error")
       end
distance (generic function with 2 methods)
```

#### 型パラメータを指定しない構造体とインスタンスの集合
- `Point` 型は, `Point{Float64}` や `Point{SbstractSting}` などのすべてのインスタンスを部分型として含む
- 多重ディスパッチでは, より具体型に近い型を優先する
- パラメトリック型の階層構造

```
julia> Point{Float64} <: Point
true

julia> Point{AbstractString} <: Point
true

```


#### 型パラメータが複数となる場合

```
julia> struct Point2{T,U}
           x::T
           y::U
       end;

julia> p = Point2(2, 3.1)
Point2{Int64, Float64}(2, 3.1)

# 関数の where キーワードにも型パラメータを記述する
julia> function distance(p::Point2{T,U}) where {T,U}
           sqrt(p.x^2 + p.y^2)
       end
distance (generic function with 3 methods)

```


### 2.4.7 パラメトリック型の階層構造
- プリミティブ型の階層構造
    - e.g., `Int < Signed < Integer < Real < Number`
- 包含関係は, `<:` もしくは `>:` で調べる


```
julia> Int <: Number
true

julia> Int >: Number
false

julia> Int <: Float64
false

```

- パラメトリック型の階層構造
    - Julia の型システムにおいて, パラメトリック型は不変
- Kotlin の場合
    - https://maku77.github.io/kotlin/generics/variant.html
    - A が B のサブタイプであったとしても、Point{A} は Point{B} のサブタイプにはならない
    - このような Generic クラスを 不変である (invariant) という
- Go の generics 関連
    - https://zenn.dev/syumai/articles/c42hdg1e0085btnen5hg

```
julia> typeof(Point)
UnionAll

julia> Point{Int} <: Point
true

# プリミティブ型では親子関係があったが
# Point 型では親子関係がない
julia> Point{Int} <: Point{Number}
false

julia> Point{Int} <: Point{Float64}
false

# もし, Point{Any} の値を, Pont{Int} が受け取ってしまったら
# 多重ディスパッチが成り立たなくなる
julia> Point{Int} <: Point{Any}
false

julia> Point{Any} <: Point{Int}
false

# Point{Int} 型は, Point{<:Any} 型に含まれる
julia> Point{Int} <: Point{<:Any}
true
```

#### 型パラメータに対する制約


```
# Point{Int} 型は, Point{<:Any} 型に含まれる
julia> Point{Int} <: Point{<:Any}
true

julia> function distance(p::Point{<:Number})
           # 処理
       end;

# 同じ意味
julia> function distance(p::Point{T<:Number})
           # 処理
       end;

```


### 2.4.8 抽象型のパラメトリック型
- 定義方法
    - `abstract type AbstractPoint{T} end;`
- `AbstractPoint{T}` を親とする型の定義


```
julia> struct Point2D{T} <: AbstractPoint{T}
           x::T
           y::T
       end;
```

#### 親子関係

```
julia> Point2D{Int} <: AbstractPoint
true

julia> Point2D{Int} <: AbstractPoint{Int}
true

julia> Point2D{Int} <: AbstractPoint{Number}
false

julia> Point2D{Int} <: AbstractPoint{<:Number}
true
```


## 2.5 コレクション
- 一連のデータを格納しておく型あるいはオブジェクトのこと
    - タプル, リスト, 辞書, 集合
    - Int64, Float64 型といったプリミティブ型などをまとめて一つのオブジェクトとして扱う
- DataStructures.jl
    - ヒープや優先度付きキュー
    - 標準以外で提供されているデータ構造
- `foo!()` など `!` がついている関数は, 引数の全てまたは一部を, 変更あるいは破棄する
    - 破壊的変更を行う
    - `push!`, `insert!`
    - `!` がついていない関数は, 破壊的変更を行わない


### 2.5.1 タプル
- 複数のオブジェクトをまとめるデータ構造
    - immutable, 値を変更できない
- 関数から複数の値をまとめて返す場合など, いくつかの値をまとめて扱いたい場合に有用
    - 要素の数が多いときや, オブジェクト同士の数値演算は, Array 型を用いる
- `(1, 2, 3)` 丸括弧で囲む


```
julia> t = (1, 2, 3)
(1, 2, 3)

julia> typeof(t)
Tuple{Int64, Int64, Int64}

# インデックスでアクセスできる
julia> t[1]
1

# 変更不可
julia> t[1] = 4
ERROR: MethodError: no method matching setindex!(::Tuple{Int64, Int64, Int64}, ::Int64, ::Int64)
Stacktrace:
 [1] top-level scope
   @ REPL[4]:1

```


#### Tuple 型の使用例
- e.g., Array 型のサイズの表現


```
julia> array = rand(4, 3)
4×3 Matrix{Float64}:
 0.27528   0.970701  0.408425
 0.34557   0.303499  0.806331
 0.478434  0.386788  0.46488
 0.244527  0.206331  0.43859

julia> size(array)
(4, 3)

```


- 関数の可変長引数


```
julia> f(x...) = x
f (generic function with 1 method)

julia> y = f(1, 2, 3)
(1, 2, 3)

julia> typeof(y)
Tuple{Int64, Int64, Int64}

```


### 2.5.2 名前付きタプル, named tuple
- 各要素に名前をつけておくことができるタプル
    - immutable, 変更不可
- `(a = 1. b = 2)`
    - NamedTuple 型
    - タプルのキーは `Symbol` 型
- 基本的に一時的に使用するオブジェクトという扱い

#### named tuple 使用例

```julia
julia> t = (a = 1, b = 2, c = 3)
(a = 1, b = 2, c = 3)

julia> t.a
1

julia> t[2]
2

julia> t[:c]
3

# キーのみを取得
julia> keys(t)
(:a, :b, :c)

# 値のみを取得
julia> values(t)
(1, 2, 3)

```


### 2.5.3 リスト
- 系列データを格納し, 値の追加や削除ができるコレクション
    - PYthon や Java のリストと同じ
- `DataStructures.jl`
    - https://github.com/JuliaCollections/DataStructures.jl


```julia
julia> list = []
Any[]

julia> list = [2, 2]
2-element Vector{Int64}:
 2
 2

julia> list = [1, 2]
2-element Vector{Int64}:
 1
 2

julia> push!(list, 3)
3-element Vector{Int64}:
 1
 2
 3

 # 末尾の要素を取り出す
julia> pop!(list)
3

julia> list
2-element Vector{Int64}:
 1
 2

 # i 番目に要素を挿入する
julia> insert!(list, 2, 4)
3-element Vector{Int64}:
 1
 4
 2

 # i 番目の要素を削除する
julia> deleteat!(list, 1)
2-element Vector{Int64}:
 4
 2

```


### 2.5.4 辞書, Dictionary
- キーと値のペアを格納するコレクション
- キーは辞書内でユニークである
    - キーから値を検索する
- https://docs.julialang.org/en/v1/base/collections/#Base.Dict


```julia
julia> d = Dict{String, Int}
Dict{String, Int64}

# 辞書の宣言時に () を忘れるとキーと値を登録できない
julia> d["a"] = 1
ERROR: MethodError: no method matching setindex!(::Type{Dict{String, Int64}}, ::Int64, ::String)
Stacktrace:
 [1] top-level scope
   @ REPL[2]:1

julia> d = Dict([("a", 1)])
Dict{String, Int64} with 1 entry:
  "a" => 1

julia> d = Dict([("b", 2)])
Dict{String, Int64} with 1 entry:
  "b" => 2

# 辞書が上書きされている
julia> d
Dict{String, Int64} with 1 entry:
  "b" => 2

# 宣言方法, Dict([("key", value), ("key", value)])
julia> d = Dict([("a", 1), ("b", 2)])
Dict{String, Int64} with 2 entries:
  "b" => 2
  "a" => 1

julia> d
Dict{String, Int64} with 2 entries:
  "b" => 2
  "a" => 1

# キーと値のペアを => でつないで初期化できる
julia> Dict("a" => 1, "b" => 2)
Dict{String, Int64} with 2 entries:
  "b" => 2
  "a" => 1

```

#### 辞書の型と初期化

```julia
# Dict{キーの型, 値の型}() と初期化する
julia> d = Dict{String, Int}()
Dict{String, Int64}()

julia> d["a"] =1; d["b"] = 2
2

julia> d
Dict{String, Int64} with 2 entries:
  "b" => 2
  "a" => 1

# 書籍の表記では初期化できない
julia> d2 = Dict{}(String)
ERROR: ArgumentError: Dict(kv): kv needs to be an iterator of tuples or pairs
Stacktrace:
 [1] Dict(kv::Type)
   @ Base ./dict.jl:132
 [2] top-level scope
   @ REPL[24]:1

# 型の情報を必ず指定する
julia> d2 = Dict{String, Any}()
Dict{String, Any}()

julia> d3 = Dict()
Dict{Any, Any}()


```


#### 辞書の値の読み書き


```julia
julia> d["a"]
1

# キーが辞書に存在しないときはエラーを返す
julia> d["c"]
ERROR: KeyError: key "c" not found
Stacktrace:
 [1] getindex(h::Dict{String, Int64}, key::String)
   @ Base ./dict.jl:482
 [2] top-level scope
   @ REPL[30]:1

julia> d["a"] = 3
3

julia> d
Dict{String, Int64} with 2 entries:
  "b" => 2
  "a" => 3

```


#### キーが辞書に含まれているか
- `haskey()` 関数を使う

```julia
julia> d = Dict("a" => 1, "b" => 2)
Dict{String, Int64} with 2 entries:
  "b" => 2
  "a" => 1

julia> haskey(d, "a")
true

julia> haskey(d, "b")
true

julia> haskey(d, "c")
false

```


#### WeakKeyDict() 型
- キーがオブジェクトへの弱い参照であるハッシュテーブルの作成
    - ハッシュテーブル内で参照されていても, ガベージコレクションされる


#### IdDict 型
- IdDict{キー, 値}() オブジェクト ID をハッシュに使うハッシュテーブルを構築する.
    - キー同士, バリュー同士は, `===` 演算子により, 等価性が判定される


### 2.5.5 集合
- 集合は, キーのみを保持する辞書
- データからユニークな要素だけを取りだす
- `Set(型)`
    `Set()` とすると `Any` 型になる

```julia
julia> s = Set()
Set{Any}()

julia> s = Set([1, 2])
Set{Int64} with 2 elements:
  2
  1

julia> typeof(s)
Set{Int64}

julia> push!(s, 3)
Set{Int64} with 3 elements:
  2
  3
  1

# 和集合, A={1,2,3}, B={3,4}, A∨B={1,2,3,4}
julia> union(s, [3,4])
Set{Int64} with 4 elements:
  4
  2
  3
  1

# 積集合, A={1,2,3}, B={3,4}, A∧B={3}
julia> intersect(s, [3,4])
Set{Int64} with 1 element:
  3

```

#### 集合演算

```julia
julia> issubset([1,2], [1,2,3])
true

julia> [1,2] \subseteq # タブキーを押す
julia> [1,2] ⊆ [1,2,3]
true

```


### 2.5.6 コレクション共通の関数


| 関数                             | 概要                       |
|----------------------------------|----------------------------|
| isempty(collection) -> Bool      | コレクションが空かどうか   |
| empty!(collection) -> collection | コレクションを空にする     |
|length(collection) -> Int         | コレクションの要素数       |
| eltype(collection) -> Type       | コレクションの型パラメータ |



### 2.5.7 コレクションのイテレーション
- for 文によるイテレーション


```julia
julia> d = Dict("a" => 1, "b" => 2, "c" => 3)
Dict{String, Int64} with 3 entries:
  "c" => 3
  "b" => 2
  "a" => 1

julia> for (key, value) in d
           println(key)
       end
c
b
a

```


#### for 文の変換

```julia
julia> for x in collection
           # 処理
       end

julia> next = iterate(collection)
# iterate() 関数によって, コレクションの最初の要素が取得される
julia> while next != nothing
           # collection の要素がなくなるまで繰り返す
           (x, state) = next
           # (x, state) のタプル
           # state は, コレクションの状態
           # 処理
           next = iterate(collection, state)
           # iterate() 関数によって, コレクションの次の要素が取得される
       end

```


## 2.6 多次元配列
- `Array{型, 次元数}` 
    - 次元数:
        - 1, ベクトル
        - 2, 行列
        - 3, テンソル
- 内部的には, １次元の配列の使用しているので, ベクトルから行列への変換などは, 値のコピーなく実行できる
- インデックスは１始まり
- 要素の順番は, column-major order
    - 列優先
- 同じ列の要素を順に列挙するのは極めて高速
- 同じ行の要素を順番に列挙するのはあまり効率的ではない


### 2.6.1 初期化
- 初期化に関する関数
- `dims` は配列のサイズ


| 関数            | 概要                  |
|-----------------|-----------------------|
| Array{T}(undef, dims...) | 値が初期化されていない配列 |
| zeros(T, dims...) | すべての値が 0 の配列 |
| ones(T, dims...) | すべての値が 1 の配列 |
| rand(T, dims...) | 一様分布でランダムに初期化した配列 |
| randn(T, dims...) | 正規分布でランダムに初期化した配列 |
| fill(x, dims...) | すべての値が x の配列 |
| fill!(A, x) | 配列 A を値 x で埋める |
| similar(A, T, dims...) | 配列 A と類似した配列 |
| reshape(A, dims...) | 配列 A のサイズを変更する |
| copy(A) | 配列 A をコピーする |
| deepcopy(A) | 配列 A をコピーする, A の要素も再帰的にコピーする |


#### 使い方


```julia
# 初期化されていない配列, 3 行, 2 列
julia> Array{Float32}(undef, 3, 2)
3×2 Matrix{Float32}:
 0.05228      4.5782f-41
 4.5782f-41   1.03552f-7
 0.000222203  4.5782f-41

# 0 で初期化した配列
julia> zeros(Float32, 3, 2)
3×2 Matrix{Float32}:
 0.0  0.0
 0.0  0.0
 0.0  0.0

# 1 で初期化した配列
julia> ones(Float32, 3, 2)
3×2 Matrix{Float32}:
 1.0  1.0
 1.0  1.0
 1.0  1.0

# 一様分布で初期化された配列
julia> rand(Float32, 3, 2)
3×2 Matrix{Float32}:
 0.317492  0.990403
 0.134426  0.781435
 0.457528  0.660034

# 正規分布で初期化された配列
julia> randn(Float32, 3, 2)
3×2 Matrix{Float32}:
 -0.48555    0.608512
 -0.413515  -2.11723
 -1.3483     0.791966

 # 1.1 で初期化した配列
julia> fill(1.1, 3, 2)
3×2 Matrix{Float64}:
 1.1  1.1
 1.1  1.1
 1.1  1.1

 # 配列の準備
julia> A = rand(Float32, 3, 2)
3×2 Matrix{Float32}:
 0.170764  0.183825
 0.838446  0.774282
 0.979092  0.683791

 # 配列 A に似た, 値が初期化されていない配列
 # 型を引き継ぐ
 # axb のサイズを引き継ぐ
julia> similar(A)
3×2 Matrix{Float32}:
 1.0f-45  1.0f-45
 1.0f-45  1.0f-45
 1.0f-45  1.0f-45

 # 配列 A に似た, 値が初期化されていない配列
 # 型を変更
julia> similar(A, Float64)
3×2 Matrix{Float64}:
 6.93282e-310    6.93282e-310
 6.93282e-310    0.0
 6.93282e-310  NaN

julia> A = rand(Float32, 3, 2)
3×2 Matrix{Float32}:
 0.246345  0.494872
 0.289044  0.0432966
 0.189577  0.473161

 # 配列のサイズを 3x2 から 2x3 へ変更
julia> reshape(A, 2, 3)
2×3 Matrix{Float32}:
 0.246345  0.189577  0.0432966
 0.289044  0.494872  0.473161

 # 配列の準備
julia> B = similar(A, Float64)
3×2 Matrix{Float64}:
 6.93282e-310  6.93282e-310
 6.93282e-310  6.93282e-310
 6.93282e-310  0.0

 # 要素自体を再帰的にコピーしない
julia> C = copy(B)
3×2 Matrix{Float64}:
 6.93282e-310  6.93282e-310
 6.93282e-310  6.93282e-310
 6.93282e-310  0.0

julia> D = deepcopy(B)
3×2 Matrix{Float64}:
 6.93282e-310  6.93282e-310
 6.93282e-310  6.93282e-310
 6.93282e-310  0.0


```


### 2.6.2 基本的な操作
- ストライド
    - 一つ一つの要素にアクセスするためにメモリ上での移動距離をバイト数で表したもの


| 関数          | 概要                |
|---------------|---------------------|
| eltype(A)    | A の要素の型  |
| length(A)    | A の要素数   |
| ndims(A)    | A の次元の数 |
| size(A) | A のサイズ |
| size(A, n)  | n 番目の次元における A のサイズ |
| strides(A) | A のストライド (要素同士が１次元配列上でいくつ離れているか |
| strinde(A, n) | n 番目の次元における A のストライド |


##### 使い方


```julia
julia> A = rand(Float32, 3, 2)
3×2 Matrix{Float32}:
 0.748757  0.877975
 0.779691  0.696333
 0.612999  0.104457

 # 配列の要素の型
julia> eltype(A)
Float32

# 配列の要素数
julia> length(A)
6

# 配列の次元の数
julia> ndims(A)
2

# 配列のサイズ
# (行, 列) のタプルで返ってきている
julia> size(A)
(3, 2)

# 配列の１次元のサイズ
julia> size(A, 1)
3

# ストライド
# 各次元ごとに要素ごとの距離を返す
# 戻り値の型は Int64
# https://paris-swc.github.io/advanced-numpy-lesson/04-container.html
julia> s = strides(A)
(1, 3)

julia> typeof(s[2])
Int64

# ストライド
# A 行列の ２次元の要素ごとの距離
julia> stride(A, 2)
3

# ストライド
# 1 行 6 列
# idx, 1,2,3,4,5,6
# e.g., 1 と 2 の要素の距離が 1
julia> a = rand(Float32, 1, 6)
1×6 Matrix{Float32}:
 0.963096  0.702786  0.932559  0.241901  0.589525  0.846759

julia> strides(a)
(1, 1)

julia> B = rand(Float32, 2, 3)
2×3 Matrix{Float32}:
 0.908282  0.0992805  0.134804
 0.71392   0.7693     0.515312

julia> strides(B)
(1, 2)

julia> stride(B, 2)
2

```


#### ストライドをもう少し
- https://paris-swc.github.io/advanced-numpy-lesson/04-container.html#Memory%20layout
- インデックスのオーダー
    - row-major order
    - column-major order

![](https://i.gyazo.com/25fecea753341e7faa8cef1a38a4b005.jpg)


- 1x6 の横ベクトル

![](https://i.gyazo.com/f761e2d5329c138c3fde14bc3d919fae.jpg)


- 6x1 の縦ベクトル

![](https://i.gyazo.com/f2bc241ba773a0fcedc4673c7c396bb1.jpg)

- 2x3 のマトリクス

![](https://i.gyazo.com/2d54ed3d41e470d2527f88e7817f953e.jpg)

```julia
julia> a = rand(UInt8, 1, 6)
1×6 Matrix{UInt8}:
 0x78  0x71  0xa7  0x5e  0x95  0x12

julia> strides(a)
(1, 1)

julia> size(a)
(1, 6)

julia> b = rand(UInt8, 6, 1)
6×1 Matrix{UInt8}:
 0xaa
 0xdb
 0x11
 0xf9
 0x24
 0x09

julia> strides(b)
(1, 6)

julia> size(b)
(6, 1)

julia> A = rand(UInt8, 2, 3)
2×3 Matrix{UInt8}:
 0xa0  0xa5  0xf9
 0x26  0x0f  0xec

julia> strides(A)
(1, 2)

julia> size(A)
(2, 3)

```


```python
>>> a = np.arange(6, dtype=np.uint8)
>>> a
array([0, 1, 2, 3, 4, 5], dtype=uint8)
>>> a.strides
(1,)
>>> a.shape
(6,)
>>> b = np.lib.stride_tricks.as_strided(a, strides=(1,1), shape=(6,1))
>>> b
array([[0],
       [1],
       [2],
       [3],
       [4],
       [5]], dtype=uint8)
>>> b.strides
(1, 1)
>>> b.shape
(6, 1)
>>> c = np.lib.stride_tricks.as_strided(a, strides=(3,1), shape=(2,3))
>>> c
array([[0, 1, 2],
       [3, 4, 5]], dtype=uint8)
>>> c.strides
(3, 1)
>>> c.shape
(2, 3)

```


### 2.6.3 インデクシング
- 配列の値を取得したり, 値を代入したり
- `collect()` 関数は, コレクションの要素を集めて配列にする関数

```julia
julia> A = collect(reshape(1:9, 3, 3))
3×3 Matrix{Int64}:
 1  4  7
 2  5  8
 3  6  9

julia> A[3, 3] = -9
-9

julia> A
3×3 Matrix{Int64}:
 1  4   7
 2  5   8
 3  6  -9

julia> A[1:2, 1:2] = [-1 -4; -2 -5]
2×2 Matrix{Int64}:
 -1  -4
 -2  -5

julia> A
3×3 Matrix{Int64}:
 -1  -4   7
 -2  -5   8
  3   6  -9

```


### 2.6.4 多次元配列の演算


| 関数      | 概要             |
|-----------|------------------|
| A + B  | A と B の加算 |
| A - B  | A と B の減算 |
| A * B  | A と B の行列の乗算 |
| A * c  | A と c の乗算 |
| A / B  | A と B の行列の右除算 |
| A \ B  | A と B の行列の左除算 |
| A .+ B | A と B の要素単位の加算 |
| A .+ c | A と c の加算 |
| A .- B | A と B の要素単位の減算 |
| A .- c | A と C の減算 |
| A .* B | A と B の要素投資の乗算 |
| A .* c | A と c の乗算 |
| A ./ B | A と B の要素単位の除算 |
| A ./ c | A と c の除算 |


### 2.6.5 ブロードキャスティング
- サイズが異なる配列同士の演算を効率的に実行する仕組み
- ブロードキャスティングができる条件
    - 配列同士の各次元の大きさが同じ
    - 次元の大きさが異なる場合, 片方のサイズ 1
- `broadcast` 関数と `broadcast!` 関数
    - `A .+ B` と同じ意味 `broadcast(+, A, B)`
    - 書式: `broadcast(関数, 引数...)`
        - 略式: `関数.(引数...)`, ドット演算 ([Dot Syntax for Vectorizing Functions](https://docs.julialang.org/en/v1/manual/functions/#man-vectorized))
        - 引数は, 配列に限定されず, タプルなど他のコレクションも指定可能


#### 行列 A のすべての要素に対して 1 を加算

##### ブロードキャストを使わない例

```julia
# ブロードキャストを使わない例
julia> A = rand(Float32, 100, 100)
100×100 Matrix{Float32}:
 0.666503  0.248429    0.63555    0.471479   0.86305    0.328116    0.409292    …  0.931346   0.293479  0.0543995  0.385661    0.138251   0.768104  0.797119
 0.666437  0.0983784   0.392675   0.57371    0.155871   0.605014    0.339838       0.776464   0.347098  0.933705   0.570366    0.347835   0.176301  0.671795
 0.976742  0.283882    0.68477    0.716425   0.354614   0.00122666  0.0812653      0.118409   0.535297  0.749607   0.695051    0.372834   0.816324  0.579094
 0.65863   0.00862622  0.606827   0.0777466  0.684209   0.0334598   0.753745       6.7234f-5  0.246851  0.593361   0.00472403  0.010237   0.440887  0.27635
 0.43213   0.0985695   0.0968812  0.488001   0.690281   0.153861    0.473643       0.472121   0.390903  0.351443   0.302619    0.148533   0.628472  0.370757
 0.361027  0.316828    0.981676   0.771886   0.996698   0.450635    0.00103843  …  0.307241   0.461473  0.652272   0.391775    0.581554   0.764276  0.875676
 0.234166  0.391842    0.397083   0.241478   0.752612   0.25036     0.587083       0.770235   0.449031  0.682428   0.674014    0.981395   0.1824    0.443235
 0.923215  0.604378    0.382935   0.10358    0.40442    0.541404    0.90397        0.832995   0.19706   0.476115   0.823327    0.347381   0.242681  0.976336
 ⋮                                                      ⋮                       ⋱                       ⋮                                           
 0.860474  0.260384    0.0104123  0.112047   0.113272   0.394971    0.253385       0.525888   0.730415  0.534455   0.550879    0.0613022  0.182068  0.785782
 0.610156  0.67757     0.178669   0.836044   0.0825194  0.363948    0.46656        0.459923   0.204402  0.964719   0.647006    0.191648   0.724247  0.933078
 0.251495  0.64156     0.161864   0.935876   0.657205   0.798601    0.300977       0.531949   0.836813  0.0563521  0.687217    0.369603   0.515214  0.605019
 0.31183   0.496711    0.0753318  0.888504   0.904687   0.874624    0.803826    …  0.283478   0.944404  0.86596    0.00813544  0.568541   0.900722  0.401953
 0.835622  0.945768    0.251092   0.649722   0.9822     0.10981     0.431658       0.57101    0.869757  0.933321   0.0634162   0.508727   0.229718  0.165494
 0.240291  0.897458    0.653193   0.312466   0.790326   0.219229    0.884319       0.688071   0.28943   0.734075   0.42533     0.878967   0.716472  0.30596
 0.808062  0.942995    0.447932   0.570009   0.4016     0.958058    0.829896       0.999235   0.604992  0.725679   0.211245    0.0543751  0.704752  0.408735
 0.909395  0.47459     0.952836   0.649475   0.0524671  0.972268    0.928214       0.338529   0.310266  0.318037   0.0940503   0.879248   0.887709  0.384945

 # 同サイズの 単位行列を作成して加算
julia> B = ones(Float32, 100, 100)
100×100 Matrix{Float32}:
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  …  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  …  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 ⋮                        ⋮                        ⋮                        ⋮    ⋱       ⋮                        ⋮                        ⋮                   
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  …  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0
 1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0     1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0  1.0

julia> A + B
100×100 Matrix{Float32}:
 1.6665   1.24843  1.63555  1.47148  1.86305  1.32812  1.40929  1.60599  1.50741  …  1.53127  1.93135  1.29348  1.0544   1.38566  1.13825  1.7681   1.79712
 1.66644  1.09838  1.39267  1.57371  1.15587  1.60501  1.33984  1.05071  1.8746      1.58942  1.77646  1.3471   1.9337   1.57037  1.34784  1.1763   1.6718
 1.97674  1.28388  1.68477  1.71642  1.35461  1.00123  1.08127  1.24488  1.58016     1.09609  1.11841  1.5353   1.74961  1.69505  1.37283  1.81632  1.57909
 1.65863  1.00863  1.60683  1.07775  1.68421  1.03346  1.75375  1.94874  1.69574     1.0015   1.00007  1.24685  1.59336  1.00472  1.01024  1.44089  1.27635
 1.43213  1.09857  1.09688  1.488    1.69028  1.15386  1.47364  1.10918  1.75895     1.8179   1.47212  1.3909   1.35144  1.30262  1.14853  1.62847  1.37076
 1.36103  1.31683  1.98168  1.77189  1.9967   1.45064  1.00104  1.04601  1.35866  …  1.84221  1.30724  1.46147  1.65227  1.39178  1.58155  1.76428  1.87568
 1.23417  1.39184  1.39708  1.24148  1.75261  1.25036  1.58708  1.75053  1.14472     1.32456  1.77024  1.44903  1.68243  1.67401  1.98139  1.1824   1.44324
 1.92321  1.60438  1.38294  1.10358  1.40442  1.5414   1.90397  1.63847  1.10281     1.58274  1.833    1.19706  1.47611  1.82333  1.34738  1.24268  1.97634
 ⋮                                            ⋮                                   ⋱                             ⋮                                   
 1.86047  1.26038  1.01041  1.11205  1.11327  1.39497  1.25338  1.48158  1.14225     1.00051  1.52589  1.73042  1.53445  1.55088  1.0613   1.18207  1.78578
 1.61016  1.67757  1.17867  1.83604  1.08252  1.36395  1.46656  1.31116  1.73501     1.03682  1.45992  1.2044   1.96472  1.64701  1.19165  1.72425  1.93308
 1.25149  1.64156  1.16186  1.93588  1.65721  1.7986   1.30098  1.4408   1.40889     1.31989  1.53195  1.83681  1.05635  1.68722  1.3696   1.51521  1.60502
 1.31183  1.49671  1.07533  1.8885   1.90469  1.87462  1.80383  1.5947   1.26088  …  1.26282  1.28348  1.9444   1.86596  1.00814  1.56854  1.90072  1.40195
 1.83562  1.94577  1.25109  1.64972  1.9822   1.10981  1.43166  1.73246  1.8432      1.09255  1.57101  1.86976  1.93332  1.06342  1.50873  1.22972  1.16549
 1.24029  1.89746  1.65319  1.31247  1.79033  1.21923  1.88432  1.68038  1.9548      1.61638  1.68807  1.28943  1.73407  1.42533  1.87897  1.71647  1.30596
 1.80806  1.943    1.44793  1.57001  1.4016   1.95806  1.8299   1.31698  1.31528     1.45824  1.99924  1.60499  1.72568  1.21124  1.05438  1.70475  1.40873
 1.9094   1.47459  1.95284  1.64948  1.05247  1.97227  1.92821  1.14882  1.13101     1.70888  1.33853  1.31027  1.31804  1.09405  1.87925  1.88771  1.38494

```

##### ブロードキャストを使った例1

```julia
julia> A = rand(Float32, 100, 100)
100×100 Matrix{Float32}:
 0.362424  0.0817847  0.205465   0.154999   0.724661   0.613015  0.950491    …  0.399387   0.833223   0.704972   0.637172   0.68454   0.887399   0.567277
 0.309287  0.527963   0.162602   0.34781    0.449616   0.584066  0.117086       0.500233   0.134729   0.809767   0.336816   0.712734  0.236652   0.147641
 0.255835  0.971876   0.768241   0.555025   0.521509   0.518939  0.134479       0.0119584  0.918403   0.642406   0.754904   0.769638  0.276642   0.0570173
 0.978004  0.0939922  0.318646   0.934322   0.953582   0.734783  0.29017        0.862785   0.0983084  0.830691   0.872788   0.464974  0.163688   0.341369
 0.93808   0.0803101  0.0101478  0.863295   0.915552   0.441396  0.0893209      0.293173   0.251209   0.799582   0.551906   0.620489  0.735846   0.782081
 0.87498   0.549075   0.967826   0.886704   0.282465   0.778521  0.252249    …  0.740902   0.772768   0.095819   0.746934   0.268456  0.619811   0.858248
 0.384825  0.68439    0.107101   0.734219   0.667332   0.854433  0.755636       0.557318   0.462408   0.48487    0.669742   0.818537  0.825139   0.0576193
 0.70972   0.634548   0.869179   0.439769   0.270292   0.362492  0.270323       0.197618   0.467668   0.385254   0.13772    0.789901  0.0222652  0.938319
 ⋮                                                     ⋮                     ⋱                        ⋮                                          
 0.580151  0.21942    0.0806725  0.388565   0.668882   0.81185   0.766787       0.699249   0.143935   0.0859228  0.642073   0.608109  0.995722   0.716143
 0.143008  0.741813   0.632618   0.217243   0.454943   0.258166  0.550736       0.799068   0.0091877  0.243564   0.198109   0.408093  0.233143   0.221513
 0.307024  0.281971   0.88866    0.538977   0.98297    0.995988  0.464931       0.876143   0.304343   0.251688   0.497572   0.217297  0.546194   0.882378
 0.684825  0.129948   0.879894   0.0137661  0.274004   0.566314  0.521192    …  0.0484935  0.527331   0.270816   0.202264   0.470972  0.240287   0.824827
 0.611186  0.568572   0.699563   0.704887   0.623806   0.213819  0.271681       0.9577     0.095863   0.164979   0.0763799  0.53468   0.614181   0.195146
 0.889524  0.335259   0.594234   0.42511    0.0707878  0.356774  0.407853       0.613399   0.0135386  0.175605   0.702628   0.872311  0.0111568  0.470898
 0.461691  0.975044   0.413291   0.877035   0.418593   0.142746  0.00876462     0.683294   0.453612   0.985488   0.335939   0.799301  0.69106    0.976482
 0.911689  0.848165   0.849851   0.412454   0.386659   0.801968  0.0139167      0.581867   0.2299     0.735512   0.83164    0.681391  0.627446   0.497519

 # ブロードキャスティングを利用
julia> A .+ 1
100×100 Matrix{Float32}:
 1.36242  1.08178  1.20547  1.155    1.72466  1.61301  1.95049  1.43249  1.29852  …  1.15813  1.39939  1.83322  1.70497  1.63717  1.68454  1.8874   1.56728
 1.30929  1.52796  1.1626   1.34781  1.44962  1.58407  1.11709  1.39513  1.23072     1.40767  1.50023  1.13473  1.80977  1.33682  1.71273  1.23665  1.14764
 1.25583  1.97188  1.76824  1.55503  1.52151  1.51894  1.13448  1.72201  1.76029     1.67801  1.01196  1.9184   1.64241  1.7549   1.76964  1.27664  1.05702
 1.978    1.09399  1.31865  1.93432  1.95358  1.73478  1.29017  1.34294  1.90462     1.3775   1.86278  1.09831  1.83069  1.87279  1.46497  1.16369  1.34137
 1.93808  1.08031  1.01015  1.86329  1.91555  1.4414   1.08932  1.32109  1.50652     1.67706  1.29317  1.25121  1.79958  1.55191  1.62049  1.73585  1.78208
 1.87498  1.54908  1.96783  1.8867   1.28247  1.77852  1.25225  1.86721  1.27571  …  1.96688  1.7409   1.77277  1.09582  1.74693  1.26846  1.61981  1.85825
 1.38482  1.68439  1.1071   1.73422  1.66733  1.85443  1.75564  1.07534  1.70534     1.20895  1.55732  1.46241  1.48487  1.66974  1.81854  1.82514  1.05762
 1.70972  1.63455  1.86918  1.43977  1.27029  1.36249  1.27032  1.68906  1.84701     1.69038  1.19762  1.46767  1.38525  1.13772  1.7899   1.02227  1.93832
 ⋮                                            ⋮                                   ⋱                             ⋮                                   
 1.58015  1.21942  1.08067  1.38856  1.66888  1.81185  1.76679  1.32025  1.29437     1.83228  1.69925  1.14393  1.08592  1.64207  1.60811  1.99572  1.71614
 1.14301  1.74181  1.63262  1.21724  1.45494  1.25817  1.55074  1.15625  1.74345     1.77618  1.79907  1.00919  1.24356  1.19811  1.40809  1.23314  1.22151
 1.30702  1.28197  1.88866  1.53898  1.98297  1.99599  1.46493  1.7754   1.09272     1.02352  1.87614  1.30434  1.25169  1.49757  1.2173   1.54619  1.88238
 1.68483  1.12995  1.87989  1.01377  1.274    1.56631  1.52119  1.64156  1.75444  …  1.68999  1.04849  1.52733  1.27082  1.20226  1.47097  1.24029  1.82483
 1.61119  1.56857  1.69956  1.70489  1.62381  1.21382  1.27168  1.8438   1.93265     1.9799   1.9577   1.09586  1.16498  1.07638  1.53468  1.61418  1.19515
 1.88952  1.33526  1.59423  1.42511  1.07079  1.35677  1.40785  1.2282   1.38212     1.4553   1.6134   1.01354  1.1756   1.70263  1.87231  1.01116  1.4709
 1.46169  1.97504  1.41329  1.87704  1.41859  1.14275  1.00876  1.54201  1.64986     1.27857  1.68329  1.45361  1.98549  1.33594  1.7993   1.69106  1.97648
 1.91169  1.84817  1.84985  1.41245  1.38666  1.80197  1.01392  1.8804   1.60761     1.33597  1.58187  1.2299   1.73551  1.83164  1.68139  1.62745  1.49752

```



##### ブロードキャストを使った例2


```julia
# 3x3 の行列
julia> A = rand(Float32, 3, 3)
3×3 Matrix{Float32}:
 0.882145  0.209033  0.510679
 0.359344  0.527326  0.32945
 0.275282  0.16508   0.889982

# 1x3 のベクトル
julia> B = ones(Float32, 1, 3)
1×3 Matrix{Float32}:
 1.0  1.0  1.0

# 3x3 の行列に 1x3 のベクトルをブロードキャスティングで加算する
julia> A .+ B
3×3 Matrix{Float32}:
 1.88214  1.20903  1.51068
 1.35934  1.52733  1.32945
 1.27528  1.16508  1.88998

# broadcast 関数を使用する
julia> broadcast(+, A, B)
3×3 Matrix{Float32}:
 1.88214  1.20903  1.51068
 1.35934  1.52733  1.32945
 1.27528  1.16508  1.88998

```


#### ドット演算の例


```julia
# sigmoid 関数を定義する
julia> sigmoid(x::Float64) = 1.0 / (1.0 + exp(-x))
sigmoid (generic function with 1 method)

julia> sigmoid(0.0)
0.5

julia> sigmoid(1.0)
0.7310585786300049

julia> A = rand(3, 2)
3×2 Matrix{Float64}:
 0.205166  0.47667
 0.365238  0.0743133
 0.481331  0.326263

# ドット演算を行う
julia> sigmoid.(A)
3×2 Matrix{Float64}:
 0.551112  0.616961
 0.590308  0.51857
 0.618062  0.58085

# ドット演算と同じ操作
julia> map(sigmoid, A)
3×2 Matrix{Float64}:
 0.551112  0.616961
 0.590308  0.51857
 0.618062  0.58085

```

##### 公式ドキュメントの例

```julia
julia> methods(sin)
# 13 methods for generic function "sin":
[1] sin(a::Float16) in Base.Math at math.jl:1159
[2] sin(a::ComplexF16) in Base.Math at math.jl:1160
[3] sin(z::Complex{T}) where T in Base at complex.jl:831
[4] sin(x::T) where T<:Union{Float32, Float64} in Base.Math at special/trig.jl:29
[5] sin(::Missing) in Base.Math at math.jl:1206
[6] sin(x::BigFloat) in Base.MPFR at mpfr.jl:728
[7] sin(x::Real) in Base.Math at math.jl:404
[8] sin(A::LinearAlgebra.Hermitian{var"#s813", S} where {var"#s813"<:Complex, S<:(AbstractMatrix{var"#s814"} where var"#s814"<:var"#s813")}) in LinearAlgebra at /home
/ysaito/src/julia-1.6.3/share/julia/stdlib/v1.6/LinearAlgebra/src/symmetric.jl:925
[9] sin(A::Union{LinearAlgebra.Hermitian{var"#s814", S}, LinearAlgebra.Symmetric{var"#s814", S}} where {var"#s814"<:Real, S}) in LinearAlgebra at /home/ysaito/src/jul
ia-1.6.3/share/julia/stdlib/v1.6/LinearAlgebra/src/symmetric.jl:921
[10] sin(D::LinearAlgebra.Diagonal) in LinearAlgebra at /home/ysaito/src/julia-1.6.3/share/julia/stdlib/v1.6/LinearAlgebra/src/diagonal.jl:603
[11] sin(A::AbstractMatrix{var"#s814"} where var"#s814"<:Real) in LinearAlgebra at /home/ysaito/src/julia-1.6.3/share/julia/stdlib/v1.6/LinearAlgebra/src/dense.jl:870
[12] sin(A::AbstractMatrix{var"#s814"} where var"#s814"<:Complex) in LinearAlgebra at /home/ysaito/src/julia-1.6.3/share/julia/stdlib/v1.6/LinearAlgebra/src/dense.jl:
877
[13] sin(J::LinearAlgebra.UniformScaling) in LinearAlgebra at /home/ysaito/src/julia-1.6.3/share/julia/stdlib/v1.6/LinearAlgebra/src/uniformscaling.jl:174

julia> a = [1.0, 2.0, 3.0]
3-element Vector{Float64}:
 1.0
 2.0
 3.0

julia> sin.(a)
3-element Vector{Float64}:
 0.8414709848078965
 0.9092974268256817
 0.1411200080598672

```


### 2.6.6 map, reduce, filter
- 配列の各要素に関数を適用して値を変換したり, 集約したり, フィルタリングする
- 書式: `map(関数, コレクション)`
    - `map` 関数,  コレクションの要素を変換する関数
        - [Base.map](https://docs.julialang.org/en/v1/base/collections/#Base.map)
    - `reduce` 関数, コレクションの要素を集約する関数
        - [Base.reduce](https://docs.julialang.org/en/v1/base/collections/#Base.reduce-Tuple{Any,%20Any})
    - `filter` 関数, コレクションの要素に対する条件評価
        - [Base.filter](https://docs.julialang.org/en/v1/base/collections/#Base.filter)


```julia
julia> A = rand(3, 2)
3×2 Matrix{Float64}:
 0.541772  0.110096
 0.165267  0.790713
 0.847019  0.0285735

# 行列 A の各要素に 1.0 を加える
julia> map(x -> x + 1.0, A)
3×2 Matrix{Float64}:
 1.54177  1.1101
 1.16527  1.79071
 1.84702  1.02857

# 行列 A のすべての要素の積
julia> reduce(*, A)
0.00018864598053094104

# 行列 A から 0.5 未満の要素を取り出す
julia> filter(x -> x < 0.5, A)
3-element Vector{Float64}:
 0.16526653120058277
 0.11009559739940444
 0.028573518542996057

```


### 2.6.7 サブ配列
- 配列の一部を表すためのオブジェクト
- 書式: `view(コレクション, 行, 列)`
- サブ配列は Go のスライスのようなもの, もとの配列への参照をもち, 値を直接持っているわけではない
    - もとの配列が変更されると, サブ配列の値も変更される
- サブ配列は, 参照情報のみであるので, メモリを節約できる


```julia
julia> A = rand(3, 3)
3×3 Matrix{Float64}:
 0.961906   0.147072  0.893516
 0.683672   0.861804  0.942962
 0.0938437  0.970717  0.0715631

# A (3x3) の, 1 行目, 2から3列目
julia> view(A, 1, 2:3)
2-element view(::Matrix{Float64}, 1, 2:3) with eltype Float64:
 0.14707177808639105
 0.8935163900878926

# A (3x3) の, 1 から 2 行目, 1 から 3 列目
julia> view(A, 1:2, :)
2×3 view(::Matrix{Float64}, 1:2, :) with eltype Float64:
 0.961906  0.147072  0.893516
 0.683672  0.861804  0.942962

```


## 2.7 モジュール
- 名前の衝突は, namespace を使うことで回避できる
- Julia のパッケージは, それぞれのパッケージが固有の名前空間を持つことでパッケージ間の名前の衝突を回避している


### 2.7.1 モジュールの機能
- 公式ドキュメント, [Mocules](https://docs.julialang.org/en/v1/manual/documentation/#Modules)
- モジュール, module
    - namespace として機能するオブジェクト
- あるモジュールの namespace に属する名前は, そのモジュール名を通して参照できる
- private な参照はできない
    - `Base.sin` のようにモジュール名で限定した名前を使うと, エクスポートされていない名前にもアクセスできる


#### 現在有効なモジュールを確認する

- `@__MODULE__` と入力することで, 現在位置でどのモジュールが有効になっているかを表示できる


```julia
julia> @__MODULE__
Main

julia> Main.gcd(12,8)
4

julia> gcd(12,8)
4

```


### 2.7.2 既存モジュールの利用
- 既存モジュールから現在のモジュールに名前を取り込む方法
- つまり, パッケージの利用方法


```julia
julia> methods(mean)
ERROR: UndefVarError: mean not defined
Stacktrace:
 [1] top-level scope
   @ REPL[5]:1

julia> using Statistics

julia> mean([1,2,3])
2.0

julia> std([1,2,3])
1.0

```


#### 指定の関数のみを取り込む
- モジュール名の後に `:` を書いた後取り込む名前を指定する
    - 複数取り込む場合は, `using Statistics: mean, std` とする


```julia
julia> using Statistics: mean

julia> mean([1,2,3])
2.0

julia> std([1,2,3])
ERROR: UndefVarError: std not defined
Stacktrace:
 [1] top-level scope
   @ REPL[4]:1

```


#### モジュール自身を取り込む
- モジュール自身を取り込むと, 関数は取り込まれない


```julia
julia> using Statistics: Statistics

julia> methods(mean)
ERROR: UndefVarError: mean not defined
Stacktrace:
 [1] top-level scope
   @ REPL[3]:1

julia> methods(Statistics.mean)
# 5 methods for generic function "mean":
[1] mean(r::AbstractRange{var"#s814"} where var"#s814"<:Real) in Statistics at /home/ysaito/src/julia-1.6.3/share/julia/stdlib/v1.6/Statistics/src/Statistics.jl:185
[2] mean(A::AbstractArray; dims) in Statistics at /home/ysaito/src/julia-1.6.3/share/julia/stdlib/v1.6/Statistics/src/Statistics.jl:164
[3] mean(itr) in Statistics at /home/ysaito/src/julia-1.6.3/share/julia/stdlib/v1.6/Statistics/src/Statistics.jl:44
[4] mean(f, A::AbstractArray; dims) in Statistics at /home/ysaito/src/julia-1.6.3/share/julia/stdlib/v1.6/Statistics/src/Statistics.jl:104
[5] mean(f, itr) in Statistics at /home/ysaito/src/julia-1.6.3/share/julia/stdlib/v1.6/Statistics/src/Statistics.jl:61

```


### 2.7.3 using 文の注意点
- `using Foo` では, モジュールのすべての名前を取り込んでしまう
- `.jl` などのスクリプトを共有する際は, 取り込む名前を指定する
- `import` 文では, 名前を暗黙的に取り込まない


### 2.7.4 新しいモジュールの定義
- モジュールの名前は大文字で始める（慣習）
- `module ... end` の間ではインデントを入れない


```julia
module SampleModule

using BigLib: thing1, thing2
import Base.show

# export 文: using 文使用時にどの名前が取り込まれるかの指定
export MyType, foo
struct MyType
    x
end

bar(x) = 2x
foo(a::MyType) = bar(a.x) + 1

show(io::IO, a::MyType) = print(io, "MyType $(a.x)")

end
```


#### REPL でのモジュール定義


```julia
julia> module Greeting
       hello(name) = println("Hello, $(name).")
       end
Main.Greeting

julia> Greeting.hello("Julia")
Hello, Julia.

```


#### 入れ子にしたモジュール定義
- 参照方法
    - `A.B1.foo(0.12)`

```julia
module A

module B1
export foo
foo(a::Float64) = a * 2
#...
end

module B2
#...
end

end
```


### 2.7.5 モジュールの相対パス指定
- `LOAD_PATH` 変数
    - `using` や `import` で指定されたモジュール名が格納される
- `module` で定義したばかりのモジュールは, `using` 文で指定してもエラーになる
    - `using` により, `LOAD_PATH` から探そうとするが, そこには格納されていないため

```julia
julia> module Greeting
       hello(name) = println("Hello, $(name).")
       end
Main.Greeting

julia> using Greeting
ERROR: ArgumentError: Package Greeting not found in current path:
- Run `import Pkg; Pkg.add("Greeting")` to install the Greeting package.

Stacktrace:
 [1] require(into::Module, mod::Symbol)
   @ Base ./loading.jl:893

```


#### 相対パス指定
- `.ModuleNmane` のように `.` をつける
- モジュール定義内で, 隣の子ノード (siblings?) のモジュールを読み込むとき
    - `..` とドットを重ねる


```julia
julia> module Greeting
       export hello
       hello(name) = println("Hello $(name).")
       end
Main.Greeting

julia> using .Greeting

julia> methods(hello)
# 1 method for generic function "hello":
[1] hello(name) in Main.Greeting at REPL[1]:3

```


### 2.7.6 ファイルの分割
- `include` 関数
    - モジュールを複数のファイルに分けて定義できる
    - ソースコードのファイルを取り込む関数
    - 引数にファイルパスを渡すと, Julia コードとして評価する
        - `include` を呼び出したファイルからの相対パス

```julia
module Foo
include("file1.jl")
include("file2.jl")
include("file3.jl")
end
```


### 2.7.7 他のモジュールで定義された関数の拡張
- `using` 文
    - 取り込んだ関数の拡張はできない
- `import` 文
    - 取り込んだ関数の拡張ができる
- `Base.length(v::Vece) = 3`
    - `import` 文を使わずに関数を拡張する方法


```julia
julia> struct Vec3{T} <: AbstractVector{T}
           x::T
           y::T
           z::T
       end

julia> import Base: length

julia> length(v::Vec3) = 3
length (generic function with 84 methods)

```


## 2.8 メタプログラミング
- プログラムを使ってプログラミングする手法
- プログラムを使ったコードの生成や書き換え
- マクロ機能 `@assert`
    - `@` で始まるものはマクロの呼び出し
        - 受け取ったコードをオブジェクトや別のコードに書き換える
- 非標準文字列リテラル, non-standard string literal
    - `r"\d+`
        - マクロの一種であり, 受け取った文字列をオブジェクトや別のコードへと変換する


### 2.8.1 シンボル
- シンボルとは
    - データ型の一種
    - 処理系の内部で使われる名前に対応する
        - e.g., `foo` という変数を使用すると, 構文解析時に `foo` という名前のシンボルが処理系の内部に作られる
- `Symbol` 型
    - 書式: `:名前`
- シンボルは同じ名前を示すオブジェクトは一つしか作られない


```julia
julia> :foo
:foo

julia> typeof(:foo)
Symbol

```

#### コンストラクタを使用した例

```julia
julia> Symbol("bar")
:bar

# コンストラクタに複数の引数を与えると結合されたシンボルができる
julia> Symbol("foo", :bar, 9)
:foobar9

# 同名のシンボルはひとつだけ
julia> Symbol("foo") == :foo
true

```


### 2.8.2 構文木の表現
- 書いたコードは, 処理系に読み込まれると構文解析され, 抽象構文木というデータ構造に変換される
- 構文木をオブジェクトして取り出す記法: `:(foo)`
    - クォート, quote と呼ぶ
- [公式ドキュメント](https://docs.julialang.org/en/v1/devdocs/ast/#Julia-ASTs)


```julia
julia> ex = :(2x + 1)
:(2x + 1)

```


#### 複数行のクォート
- `quote ... end` キーワードを使う


```julia
julia> quote
           2x + 1
           3y + 2
       end
quote
    #= REPL[7]:2 =#
    2x + 1
    #= REPL[7]:3 =#
    3y + 2
end

```

#### Expr 型のオブジェクト
- 構文木は `Expr` 型のオブジェクト
    - "expression" の略
    - `head` フィールド
        - 構文木の種類
    - `args` フィールド
        - 構成要素の保持


#### dump 関数
- `dump()` 関数で, 構成要素を表示できる

```julia
julia> dump(ex)
Expr
  # call というシンボルが格納されている
  # この構文木が関数呼び出しであることを示している
  head: Symbol call
  # args フィールドの最初の要素が呼び出す関数名
  # 2x と 1 を引数として + 関数を呼び出す
  args: Array{Any}((3,))
    # 3 つのシンボル
    # +, 2x に対応する別の構文木, 整数 1
    1: Symbol +
    2: Expr
      head: Symbol call
      # 2 と x を引数として, * 関数を呼び出す
      args: Array{Any}((3,))
        1: Symbol *
        2: Int64 2
        3: Symbol x
    3: Int64 1

```


#### その他の構文木
- `x = 10`


```julia
julia> dump(:(x = 10))
Expr
  # = というシンボルが格納されている
  # 代入を表す
  head: Symbol =
  args: Array{Any}((2,))
    1: Symbol x
    2: Int64 10

```


### 2.8.3 構文木の補間
- 補間, interpolation
- クォートで作られた構文木には, 別の構文木やリテラルを埋め込める
    - `$ex` と `$(ex)` は等価
    - `$(func(ex))` 関数を適用した結果を埋め込める


```julia
julia> ex = 1
1

# 整数リテラルの補間
julia> :(2x + $(ex))
:(2x + 1)

julia> ex = :(3y + 1)
:(3y + 1)

# 構文木の補間
julia> :(2x + $(ex))
:(2x + (3y + 1))

```


#### 補間するものがシンボルの場合
- `$(ex)` の結果は, `y` になる
- シンボルとして埋め込む場合は `$(QuoteNode(ex))` を利用する


```julia
julia> ex = :y
:y

julia> :(2x + $(ex))
:(2x + y)

julia> :(2x + $(QuoteNode(ex)))
:(2x + :y)

julia> 
```


### 2.8.4 構文木の評価
- 構文木は, eval 関数で評価できる
- 評価とは, 構文木を実行し, その結果を得ること
- `eval` 関数は, 構文木を引数として受け取り, 現在のモジュールでその構文木を実行し結果を返す


```julia
julia> x = 10
10

# 変数 x は 10 に束縛されている
# 2 * 10 + 1 を計算している
julia> eval(:(2x + 1))
21

```


#### 評価のスコープ
- 評価は常にモジュールのグローバルスコープで行われる


```julia
julia> function test()
           # 関数内のローカル変数を定義
           x = "local"
           # eval 関数は Main モジュールで実行される
           # つまりグローバル変数としての X に代入している
           eval(:(x = "global"))
           println(x)
       end
test (generic function with 1 method)

julia> test()
local

julia> x
"global"

```


#### eval 関数を利用したメタプログラミング
- ビットグラフを持つ３つの定数を導入する


```julia
julia> for (i, name) in enumerate([:A, :B, :C])
           eval(:(const $(Symbol(:FLAG_, name)) = $(UInt16(1) << (i - 1))))
       end

julia> FLAG_A, FLAG_B, FLAG_C
(0x0001, 0x0002, 0x0004)

```


#### @eval マクロ
- `eval` 関数と同じ機能を有する
-  `@eval` は, 与えられたコードをクォートし, その結果を `eval` 関数で評価する


```julia
julia> for (i, name) in enumerate([:A, :B, :C])
           @eval const $(Symbol(:FLAG_, name)) = $(UInt16(1) << (i - 1))
       end

julia> FLAG_A, FLAG_B, FLAG_C
(0x0001, 0x0002, 0x0004)

```


### 2.8.5 マクロの機能
- マクロをは与えられたコードを別のコードに変換してから実行する仕組み
- `@` 記号で始まる
- マクロの展開, expansion
    - 処理系がマクロ呼び出しに渡されたコードを変換して別のコードに置き換える処理
- 展開の結果は, `@macroexpand` マクロで確認できる
- `@macroexpand`
    - 与えられた式にあるマクロ呼び出しを添加した構文木を返す
- マクロ呼び出しの展開は, コンパイルの早い段階で行われる
- [公式ドキュメント](https://docs.julialang.org/en/v1/manual/metaprogramming/#man-macros)


```julia
julia> @macroexpand @assert x > 0
:(if x > 0
      nothing
  else
      Base.throw(Base.AssertionError("x > 0"))
  end)

```


#### マクロの呼び出し
- 2 種類の呼び出し, 引数にカッコありとなし
    - `@macro(ex1, ex2, ex3)`
    - `@macro ex1, ex2, ex3`
        - 必要がなければ, カッコは省略する


```julia
julia> :(@macro x + y) == :(@macro(x + y))
true

julia> :(@macro x +) == :(@macro(x, +))
true

```


#### 文字列のみを受け取るマクロ
- 非標準文字列リテラル, non-standard string literal
    - `foo_str`, suffic が `_str`
        - `@foo_str` は `foo"..."` のように呼び出せる
    - 主に特定のオブジェクトのリテラルを定義するのに使われる
    - e.g., 正規表現リテラル


### 2.8.6 標準ライブラリにあるマクロ
- コンパイラへのヒント
    - `@inbounds`, `@inline`, `@fastmath`
- 構文の拡張
    - `@assert`, `@enum`, `@view`
- 開発の補助
    - `@less`, `2time`, `@code_typed`
- 特殊なリテラル
    - `@r_str`, `@big_str`


#### コンパイラへのヒントを出すマクロ
- 最適化などのヒントになる情報を構文kに差し込むことでコンパイラに渡すマクロ
- `@inbounds` マクロ
    - 配列要素の参照が配列の有効な範囲に収まることをプラグラマが保証するので, 実行時に範囲のチェックを省いても良い
- `@inline` マクロ
    - 関数を積極的にインラインスべきというヒント
- `@fastmath` マクロ
    - 浮動小数点数の計算に関して IEEE754 の制約を超えて最適化することを許可するマクロ


#### 構文の拡張をするマクロ
- プログラマが手で書くには面倒な処理を自動化するマクロ
- `@asser` マクロ
    - 与えられた式の条件が成立するかどうかを実行時にチェックし, その条件が成立しなければ `AssertionError` 例外を送出する
- `@enum` マクロ
    - C の enum 構文に相当する機能を提供する
- `@view` マクロ
    - 配列の一部をコピーではなく参照するようにするマクロ


#### 開発補助のためのマクロ
- REPL などの対話型環境で用いられるマクロ
- `@less` マクロ
    - 関数呼び出しの式を受け取って, 呼び出されるメソッドのソースコードを表示する
- `@time` マクロ
    - 処理を受け取ってその実行にかかった時間やメモリ使用量を表示する
- `@code_typed` マクロ
    - 関数呼び出しの式を受け取って, コンパイラによる型推論の結果を表示する


#### 特殊なリテラルを定義するマクロ
- 非標準文字列リテラルとして機能し, 特定のオブジェクトを作るマクロ
- `@r_str` マクロ
    - 正規表現のオブジェクトを作るのに使われる
- `@big_str` マクロ
    - `BigInt` 型や, `BigFloat` 型などの可変長サイズの整数や, 浮動小数点数を作るのに使われる


### 2.8.7 マクロの定義
- `macro` キーワード
    - マクロ名は, 関数名と同様の名前が使える
    - 引数には, 呼び出し側で与えられた構文木やリテラルが入る
    - `return` で指定された式か, 最後に評価された式が結果として返される


```julia
macro マクロ名(引数1, 引数2, ...)
    # 処理
end
```


#### マクロ定義の例
- Julia では, マクロの展開をするときに, デフォルトで式の中の識別子をマクロが定義されてモジュールのフローバル変数に置き換える
    - これを防ぐには, `esc` 関数を使う
- `esc` 関数は, 構文木にある識別子を別の識別子に置き換えず, そのままにする


```julia
julia> macro plus1(ex)
           :($(ex) + 1)
       end
@plus1 (macro with 1 method)

# 変数 x が Main モジュールのグローバル変数 x になっている
julia> @macroexpand @plus1 2x
:(2 * Main.x + 1)

julia> x = 10
10

julia> @plus1 2x
21

# esc 関数で, 変数 x をグローバル変数に変換しないようにする
julia> macro plus1(ex)
           :($(esc(ex)) + 1)
       end
@plus1 (macro with 1 method)

# 変数 x が, ローカル変数となっている
julia> @macroexpand @plus1 2x
:(2x + 1)

```


### 2.8.8 識別子の変換規則
- マクロ展開時に, 識別子がローカル変数に変換される例外
    - `global` 宣言無しで代入されたとき
    - `local` 宣言があるとき
    - 関数定義の引数であるとき
- ローカル変数と解釈された識別子は, マクロ展開時に新しい変数に置き換えられる
    - 衛生的マクロ, hygienic macro


```julia
julia> macro time_ns(ex)
           quote
               t1 = time_ns()
               val = $(esc(ex))
               t2 = time_ns()
               val, Int(t2 - t1)
           end
       end
@time_ns (macro with 1 method)

# 計算結果と, 実行時間のタプルを返す
julia> @time_ns sum(randn(1000))
(-48.784427777440165, 112017647)

# ２回目の実行では, 計算が高速になる
julia> @time_ns sum(randn(1000))
(-54.506982367056324, 19110)

julia> @macroexpand @time_ns sum(randn(1000))
quote
    #= REPL[1]:3 =#
    # Main モジュールの time_ns() に変換されている
    var"#7#t1" = Main.time_ns()
    #= REPL[1]:4 =#
    # esc 関数でエスケープした, ex つまり, sum(randn(1000)) はそのまま
    var"#8#val" = sum(randn(1000))
    #= REPL[1]:5 =#
    var"#9#t2" = Main.time_ns()
    #= REPL[1]:6 =#
    (var"#8#val", Main.Int(var"#9#t2" - var"#7#t1"))
end

```


#### マクロ内の識別子の変換タイミング
- `esc` 関数でエスケープされていれば, 識別子は変換されない
- 代入, `local` 宣言, 関数引数のいずれかであれば, 新しいローカル変数が生成される
- 上記のいずれにも当てはまらない場合, マクロを定義したモジュールのグローバル変数に変換される



## 2.9 C 言語の呼び出し
- 動的リンクライブラリとしてビルドされていれば, Julia から利用できる
    - Fortran ライブラリについて[公式ドキュメント](https://docs.julialang.org/en/v1/manual/calling-c-and-fortran-code/#Calling-C-and-Fortran-Code)


### 2.9.1 ccall 構文
- 使い方
    - `ccall(C の関数, 戻り値の型, 引数の型, 引数1, 引数2, ...)`
- `ccall` 自体を引数として別の関数に渡したりなどはできない


```julia
# sin 関数の呼び出し
julia> ccall(:sin, Cdouble, (Cdouble,), 1.0)
0.8414709848078965

```

- `:sin`
    - 呼び出す関数
    - 標準ライブラリ以外は, ライブラリ名も必要
        - 書式: `(関数名, ライブラリ名)`
            - e.g., `(:compress, "libz")`
- `Cdouble`
    - 戻り値の型が C の double 型に対応することを指定している
    - 他の例
        - `int` 型の別名, `Cint`
        - 戻り値が `void`, `Cvoid` 型
    - 呼び出す C の関数のマニュアルやヘッダファイルに書かれた宣言を見て決める
    - 戻り値の型や引数の型を謝ると正しく呼び出せない
- `(Cdouble,)`
    - 関数に渡す引数の型を指定するタプル
    - 引数は一つしかないので, 要素が一つのタプル
- `1.0`
    - 実際に `sin` 数に渡される引数
    - 第３引数に指定されたデータ型に変換されてから渡される
    - 変換は `Base.cconvert` 関数で行われる
        - `ccall` 構文に指定した引数の型と実際の引数の型が厳密に一致している必要はない


```julia
julia> Base.cconvert(Cdouble, 1) isa Cdouble
true

```


### 2.9.2 ポインタの受け渡し
- 引数がポインタ型
    - e.g.,
        - `char *name` は, 末端が NUL で埋められた文字列表現
        - Julia の `Cstring` 型が対応
- 戻り値がポインタ型
    - `unsafe_string` 関数を使って, C の文字列表現から, Julia の文字列表現へ変換する
    - 正しく文字列を刺さないポインタを渡された場合には, 深刻な問題を引き起こす可能性がある


```julia
# getenv 関数を呼び出す
julia> ccall(:getenv, Cstring, (Cstring,), "HOME")
Cstring(0x00007ffd163d02c8)

# ポインタから文字列を読み出す
julia> unsafe_string(ans)
"/home/ysaito"

# 存在しない環境変数を取得しようとすると
# NUL ポインタを返す
julia> ccall(:getenv, Cstring, (Cstring,), "NOTEXISTS")
Cstring(0x0000000000000000)

# Julia の文字列に変換できないので例外を返す
julia> unsafe_string(ans)
ERROR: ArgumentError: cannot convert NULL to string
Stacktrace:
 [1] unsafe_string
   @ ./strings/string.jl:70 [inlined]
 [2] unsafe_string(s::Cstring)
   @ Base ./c.jl:193
 [3] top-level scope
   @ REPL[8]:1

```


#### 文字列以外のポインタ処理
- C の関数が `int*` や `double[]` のようなポインタ型を引数として受け取る場合には, Julia 側では, `Ref` 関数で参照を作る
- Julia の値は `Ref` 関数でラップできる
- ラップされた値を取り出すには, `[]` でデリファレンスする


```julia
# 参照の作成
julia> x = Ref(0)
Base.RefValue{Int64}(0)

# デリファレンス
julia> x[]
0

# 参照先の更新
julia> x[] += 1
1

julia> x
Base.RefValue{Int64}(1)

# デリファレンス
julia> x[]
1

```


#### インクリメントする C ライブラリの呼び出し例

```clang
// libinc.c
void inc(int* x) {
	*x += 1;
}
```

```shell
$ gcc -std=c99 -shared -fPIC -o libinc.so libinc.c
```


```julia
julia> x = Ref{Cint}(0)
Base.RefValue{Int32}(0)

julia> x[]
0

julia> ccall((:inc, "./libinc.so"), Cvoid, (Ref{Cint},), x)

julia> x[]
1

```


#### 配列の受け渡し例

```clang
// libsum.c
#include <stddef.h>

double sum(const double xs[], size_t n) {
	double s = 0;
	for (size_t i = 0; i < n; i++)
		s += xs[i];
	return s;
}
```

```shell
$ gcc -std=c99 -shared -fPIC -o libsum.so libsum.c
```


```julia
julia> xs = [1.0, 2.0, 3.0]
3-element Vector{Float64}:
 1.0
 2.0
 3.0

julia> ccall((:sum, "./libsum.so"), Cdouble, (Ref{Cdouble}, Csize_t), xs, length(xs))
6.0

```


### 2.9.3 構造体の受け渡し
- C の `struct` で定義された構造体と, Julia の `struct` や `mutable struct` で定義された複合型のメモリレイアウトには互換性がある


```clang
// libpoint.c
#include <math.h>

typedef struct {
	double x;
	double y;
} point2d_t;

double distance(point2d_t p) {
	return sqrt(p.x * p.x + p.y * p.y);
}
```


```shell
gcc -std=c99 -shared -fPIC -o libpoint.so libpoint.c
```

```julia
julia> struct Point2D
           x::Cdouble
           y::Cdouble
       end

julia> ccall((:distance, "./libpoint.so"), Cdouble, (Point2D,), Point2D(1,2))
2.23606797749979

```


#### 関数を C に加えて値を更新してみる

```clang
// libpoint.c
#include <math.h>

typedef struct {
	double x;
	double y;
} point2d_t;

double distance(point2d_t p) {
	return sqrt(p.x * p.x + p.y * p.y);
}

void move(point2d_t *p, double dx, double dy) {
	p->x += dx;
	p->y += dy;
}
```


```shell
$ gcc -std=c99 -shared -fPIC -o libpoint.so libpoint.c
```


```julia
julia> mutable struct Point2D
           x::Cdouble
           y::Cdouble
       end

julia> p = Point2D(0,0)
Point2D(0.0, 0.0)

julia> ccall((:move, "./libpoint.so"), Cvoid, (Ref{Point2D}, Cdouble, Cdouble), Ref(p), 1, 3)

# p の座標が変更されている
julia> p
Point2D(1.0, 3.0)

```


## 2.10 外部プログラムの呼び出し
- コマンドの作成・実行
- パイプライン処理


### 2.10.1 コマンドの作成・実行
- バッククォートで囲み, 関数に渡すことで実行される
- `Cmd` 型オブジェクトを `run` 関数に渡すことで, 実行される
- `run` 関数は, 実行したコマンドのプロセスを `Process` 型のオブジェクトとして返す


```julia
# コマンドオブジェクトの作成
julia> `ls`
`ls`

# コマンドの実行
julia> run(ans)
README.md  README.md~  libinc.c  libinc.so  libpoint.c  libpoint.c~  libpoint.so  libsum.c  libsum.c~  libsum.so
Process(`ls`, ProcessExited(0))
```


#### 標準出力の取得
- `red` 関数を使う


```julia
# 標準出力を文字列として取得
julia> read(`ls`, String)
"README.md\nREADME.md~\nlibinc.c\nlibinc.so\nlibpoint.c\nlibpoint.c~\nlibpoint.so\nlibsum.c\nlibsum.c~\nlibsum.so\n"

# 行ごとに処理
julia> for line in eachline(`find . -type f`)
           @show line
       end
line = "./libsum.c~"
line = "./.libsum.c.un~"
line = "./README.md"
line = "./libinc.c"
line = "./libpoint.so"
line = "./.libinc.c.un~"
line = "./libsum.c"
line = "./libpoint.c"
line = "./libsum.so"
line = "./libpoint.c~"
line = "./libinc.so"
line = "./.README.md.un~"
line = "./README.md~"
line = "./.libpoint.c.un~"

```


#### 標準入力に書き込みを行う
- `open` 関数を使う
- コマンドはデフォルトで同期実行されるので, 長時間かかるコマンドでもその終了まで待つ
- 呼び出したプロセスが正常に終了しなかった場合には例外が送出される


```julia
julia> open(`wc -l`, "w", stdout) do output
           for _ in 1:10
               println(output, "hi!")
           end
       end
10

julia> @time run(`sleep 10`)
 10.001107 seconds (42 allocations: 1.719 KiB)
Process(`sleep 10`, ProcessExited(0))

julia> run(`ls --optino-not-exist`)
ls: unrecognized option '--optino-not-exist'
Try 'ls --help' for more information.
ERROR: failed process: Process(`ls --optino-not-exist`, ProcessExited(2)) [2]

Stacktrace:
 [1] pipeline_error
   @ ./process.jl:525 [inlined]
 [2] run(::Cmd; wait::Bool)
   @ Base ./process.jl:440
 [3] run(::Cmd)
   @ Base ./process.jl:438
 [4] top-level scope
   @ REPL[9]:1

```


### 2.10.2 コマンド実行の注意点
- Julia で実行したコマンドは, shell を経由しない
- shell の機能は使えない
- shell の機能が必要な場合には, 明示的にシェルを実行する


```julia
# bash の -c オプションでコマンドを実行する
julia> run(`bash -c 'ls *.c'`)
libinc.c  libpoint.c  libsum.c
Process(`bash -c 'ls *.c'`, ProcessExited(0))

julia> run(`bash -c 'find . -type f | wc -l'`)
14
Process(`bash -c 'find . -type f | wc -l'`, ProcessExited(0))

```


### 2.10.3 パイプライン処理
- `pipeline` 関数を使うことで, shell の機能を使わずに, コマンドのパイプライン処理ができる
- ３つ以上の引数を取ることもできる
- 文字列を引数に渡した場合は, ファイルパスとして解釈される
    - コマンドの左側にあると, コマンドへの入力
    - 右側にあると, コマンドの出力を受け取ってファイルへ保存する


```julia
julia> run(`ls`)
README.md  README.md~  libinc.c  libinc.so  libpoint.c  libpoint.c~  libpoint.so  libsum.c  libsum.c~  libsum.so
Process(`ls`, ProcessExited(0))

julia> pipeline(`cat libinc.c`, `wc -l`)
pipeline(`cat libinc.c`, stdout=`wc -l`)

julia> run(ans)
4
Base.ProcessChain(Base.Process[Process(`cat libinc.c`, ProcessExited(0)), Process(`wc -l`, ProcessExited(0))], Base.DevNull(), Base.DevNull(), Base.DevNull())

```


### 2.10.4 より発展的なコマンドの作成方法
- 動的にコマンドを作成できる
- 補間など
- 配列を利用して, コマンド全体を作成できる


```julia
julia> msg = "hello"
"hello"

# 引数を補間
julia> `echo $(msg)`
`echo hello`

julia> run(ans)
hello
Process(`echo hello`, ProcessExited(0))

julia> cmd = "echo"
"echo"

# コマンドを補間
julia> run(`$(cmd) hello`)
hello
Process(`echo hello`, ProcessExited(0))

# 引数に渡す文字列が空白を含んでいても, １つの引数になる
julia> `touch $("foo bar")`
`touch 'foo bar'`

# 複数の引数を, 配列で補間
julia> `touch $(["foo", "bar"])`
`touch foo bar`

# 複数の引数を, タプルで補間
julia> `touch $(("foo", "bar"))`
`touch foo bar`

```


#### 環境変数やディレクトリの指定
- `Cmd` 型のコンストラクタを利用する
- 環境変数の設定
    - `env` キーワード引数に環境変数を収めた辞書を渡す
- 実行ディレクトリの設定
    - `dir` キーワード引数にディレクトリへのパスを渡す


```julia
julia> run(`locale`)
LANG=ja_JP.UTF-8
LANGUAGE=en_US:en
LC_CTYPE="ja_JP.UTF-8"
LC_NUMERIC=en_GB.UTF-8
LC_TIME=en_GB.UTF-8
LC_COLLATE="ja_JP.UTF-8"
LC_MONETARY=en_GB.UTF-8
LC_MESSAGES="ja_JP.UTF-8"
LC_PAPER=en_GB.UTF-8
LC_NAME=en_GB.UTF-8
LC_ADDRESS=en_GB.UTF-8
LC_TELEPHONE=en_GB.UTF-8
LC_MEASUREMENT=en_GB.UTF-8
LC_IDENTIFICATION=en_GB.UTF-8
LC_ALL=
Process(`locale`, ProcessExited(0))

julia> run(Cmd(`locale`, env = Dict("LANG" => "C")))
LANG=C
LANGUAGE=
LC_CTYPE="C"
LC_NUMERIC="C"
LC_TIME="C"
LC_COLLATE="C"
LC_MONETARY="C"
LC_MESSAGES="C"
LC_PAPER="C"
LC_NAME="C"
LC_ADDRESS="C"
LC_TELEPHONE="C"
LC_MEASUREMENT="C"
LC_IDENTIFICATION="C"
LC_ALL=
Process(setenv(`locale`,["LANG=C"]), ProcessExited(0))

julia> run(`pwd`)
/home/ysaito/projects/julia/Learn-Julia-Programming-from-Scratch-mokumoku/ch02
Process(`pwd`, ProcessExited(0))

julia> run(Cmd(`pwd`, dir="/usr/local/bin"))
/usr/local/bin
Process(setenv(`pwd`; dir="/usr/local/bin"), ProcessExited(0))

```


#### コマンドが存在するか
- `Sys.which` 関数
    - `which` と同じ使用方法


```julia
julia> Sys.which("ls")
"/usr/bin/ls"

julia> Sys.which("elixirc")

julia> Sys.which("elixirc") === nothing
true

```


## 2.11 パッケージ
- Julia のパッケージは, 特定の構造を撮ったディレクトリ


### 2.11.1 パッケージ管理の基本
- `julia>` のプロンプト時に `]` キーを押す
- `pkg> status` コマンド
    - インストール済みの外部パッケージ一覧


```julia
# ] キーを押す
julia> 

# BS キーで戻る
(@v1.6) pkg> 

julia> 

# インストール済みの外部パッケージ一覧
(@v1.6) pkg> status
      Status `~/.julia/environments/v1.6/Project.toml`
  [8f4d0f93] Conda v1.5.2
  [438e738f] PyCall v1.92.3
  [d330b81b] PyPlot v2.10.0

# Distributions パッケージのインストール
(@v1.6) pkg> add Distributions
    Updating registry at `~/.julia/registries/General`
   Resolving package versions...
   Installed PDMats ────────────── v0.11.1
   Installed InverseFunctions ──── v0.1.1
   Installed Rmath ─────────────── v0.7.0
   Installed Rmath_jll ─────────── v0.3.0+0
   Installed DataStructures ────── v0.18.10
   Installed StatsFuns ─────────── v0.9.12
   Installed SpecialFunctions ──── v1.8.1
   Installed StatsAPI ──────────── v1.0.0
   Installed DocStringExtensions ─ v0.8.6
   Installed IrrationalConstants ─ v0.1.1
   Installed DataAPI ───────────── v1.9.0
   Installed QuadGK ────────────── v2.4.2
   Installed LogExpFunctions ───── v0.3.4
   Installed Distributions ─────── v0.25.21
   Installed SortingAlgorithms ─── v1.0.1
   Installed FillArrays ────────── v0.12.7
   Installed OpenSpecFun_jll ───── v0.5.5+0
   Installed Missings ──────────── v1.0.2
   Installed Compat ────────────── v3.39.0
   Installed Preferences ───────── v1.2.2
   Installed JLLWrappers ───────── v1.3.0
   Installed StatsBase ─────────── v0.33.12
   Installed OrderedCollections ── v1.4.1
   Installed ChainRulesCore ────── v1.11.0
  Downloaded artifact: Rmath
  Downloaded artifact: OpenSpecFun
    Updating `~/.julia/environments/v1.6/Project.toml`
  [31c24e10] + Distributions v0.25.21
    Updating `~/.julia/environments/v1.6/Manifest.toml`
  [d360d2e6] + ChainRulesCore v1.11.0
  [34da2185] + Compat v3.39.0
  [9a962f9c] + DataAPI v1.9.0
  [864edb3b] + DataStructures v0.18.10
  [31c24e10] + Distributions v0.25.21
  [ffbed154] + DocStringExtensions v0.8.6
  [1a297f60] + FillArrays v0.12.7
  [3587e190] + InverseFunctions v0.1.1
  [92d709cd] + IrrationalConstants v0.1.1
  [692b3bcd] + JLLWrappers v1.3.0
  [2ab3a3ac] + LogExpFunctions v0.3.4
  [e1d29d7a] + Missings v1.0.2
  [bac558e1] + OrderedCollections v1.4.1
  [90014a1f] + PDMats v0.11.1
  [21216c6a] + Preferences v1.2.2
  [1fd47b50] + QuadGK v2.4.2
  [79098fc4] + Rmath v0.7.0
  [a2af1166] + SortingAlgorithms v1.0.1
  [276daf66] + SpecialFunctions v1.8.1
  [82ae8749] + StatsAPI v1.0.0
  [2913bbd2] + StatsBase v0.33.12
  [4c63d2b9] + StatsFuns v0.9.12
  [efe28fd5] + OpenSpecFun_jll v0.5.5+0
  [f50d1b31] + Rmath_jll v0.3.0+0
  [0dad84c5] + ArgTools
  [56f22d72] + Artifacts
  [8bb1440f] + DelimitedFiles
  [8ba89e20] + Distributed
  [f43a241f] + Downloads
  [b27032c2] + LibCURL
  [76f85450] + LibGit2
  [ca575930] + NetworkOptions
  [44cfe95a] + Pkg
  [3fa0cd96] + REPL
  [ea8e919c] + SHA
  [1a1011a3] + SharedArrays
  [4607b0f0] + SuiteSparse
  [fa267f1f] + TOML
  [a4e569a6] + Tar
  [cf7118a7] + UUIDs
  [e66e0078] + CompilerSupportLibraries_jll
  [deac9b47] + LibCURL_jll
  [29816b5a] + LibSSH2_jll
  [c8ffd9c3] + MbedTLS_jll
  [14a3606d] + MozillaCACerts_jll
  [05823500] + OpenLibm_jll
  [83775a58] + Zlib_jll
  [8e850ede] + nghttp2_jll
  [3f19e933] + p7zip_jll
Precompiling project...
  29 dependencies successfully precompiled in 13 seconds (11 already precompiled, 1 skipped during auto due to previous errors)

# パッケージのアップデート
(@v1.6) pkg> update
    Updating registry at `~/.julia/registries/General`
   Installed VersionParsing ─ v1.2.1
   Installed Parsers ──────── v2.1.0
   Installed PyCall ───────── v1.92.5
    Updating `~/.julia/environments/v1.6/Project.toml`
  [438e738f] ↑ PyCall v1.92.3 ⇒ v1.92.5
    Updating `~/.julia/environments/v1.6/Manifest.toml`
  [69de0a69] ↑ Parsers v2.0.5 ⇒ v2.1.0
  [438e738f] ↑ PyCall v1.92.3 ⇒ v1.92.5
  [81def892] ↑ VersionParsing v1.2.0 ⇒ v1.2.1
    Building PyCall → `~/.julia/scratchspaces/44cfe95a-1eb2-52ea-b672-e2afdf69b78f/4ba3651d33ef76e24fef6a598b63ffd1c5e1cd17/build.log`

# 不要ファイルの削除
(@v1.6) pkg> gc
      Active manifest files: 1 found
      Active artifact files: 2 found
      Active scratchspaces: 3 found
     Deleted no artifacts, repos, packages or scratchspaces

```


### 2.11.2 プロジェクトのパッケージ管理
- `Project.toml`
    - 現在のプロジェクトが依存しているパッケージを管理する
- `Manifest.toml`
    - 使われているパッケージの正確なバージョンやインストール場所を管理する
    - git 管理に含めない


```shell
# プロジェクト用のディレクトリを作る
$ mkdir ./pkgExample
$ cd $_
```


```toml
# プロジェクト用の toml ファイルを作る
# Project.toml
name = "pkgExample"
```


```julia
# Pkg モードで activate する
(@v1.6) pkg> activate .
  Activating environment at `~/projects/julia/Learn-Julia-Programming-from-Scratch-mokumoku/ch02/pkgExample/Project.toml`

# 最初はパッケージはない
(pkgExample) pkg> status
      Status `~/projects/julia/Learn-Julia-Programming-from-Scratch-mokumoku/ch02/pkgExample/Project.toml` (empty project)

# パッケージを追加する
(pkgExample) pkg> add Distributions
    Updating registry at `~/.julia/registries/General`
   Resolving package versions...
    Updating `~/projects/julia/Learn-Julia-Programming-from-Scratch-mokumoku/ch02/pkgExample/Project.toml`
  [31c24e10] + Distributions v0.25.21
    Updating `~/projects/julia/Learn-Julia-Programming-from-Scratch-mokumoku/ch02/pkgExample/Manifest.toml`
  [d360d2e6] + ChainRulesCore v1.11.0
  [34da2185] + Compat v3.39.0
  [9a962f9c] + DataAPI v1.9.0
  [864edb3b] + DataStructures v0.18.10
  [31c24e10] + Distributions v0.25.21
  [ffbed154] + DocStringExtensions v0.8.6
  [1a297f60] + FillArrays v0.12.7
  [3587e190] + InverseFunctions v0.1.1
  [92d709cd] + IrrationalConstants v0.1.1
  [692b3bcd] + JLLWrappers v1.3.0
  [2ab3a3ac] + LogExpFunctions v0.3.4
  [e1d29d7a] + Missings v1.0.2
  [bac558e1] + OrderedCollections v1.4.1
  [90014a1f] + PDMats v0.11.1
  [21216c6a] + Preferences v1.2.2
  [1fd47b50] + QuadGK v2.4.2
  [189a3867] + Reexport v1.2.2
  [79098fc4] + Rmath v0.7.0
  [a2af1166] + SortingAlgorithms v1.0.1
  [276daf66] + SpecialFunctions v1.8.1
  [82ae8749] + StatsAPI v1.0.0
  [2913bbd2] + StatsBase v0.33.12
  [4c63d2b9] + StatsFuns v0.9.12
  [efe28fd5] + OpenSpecFun_jll v0.5.5+0
  [f50d1b31] + Rmath_jll v0.3.0+0
  [0dad84c5] + ArgTools
  [56f22d72] + Artifacts
  [2a0f44e3] + Base64
  [ade2ca70] + Dates
  [8bb1440f] + DelimitedFiles
  [8ba89e20] + Distributed
  [f43a241f] + Downloads
  [b77e0a4c] + InteractiveUtils
  [b27032c2] + LibCURL
  [76f85450] + LibGit2
  [8f399da3] + Libdl
  [37e2e46d] + LinearAlgebra
  [56ddb016] + Logging
  [d6f4376e] + Markdown
  [a63ad114] + Mmap
  [ca575930] + NetworkOptions
  [44cfe95a] + Pkg
  [de0858da] + Printf
  [3fa0cd96] + REPL
  [9a3f8284] + Random
  [ea8e919c] + SHA
  [9e88b42a] + Serialization
  [1a1011a3] + SharedArrays
  [6462fe0b] + Sockets
  [2f01184e] + SparseArrays
  [10745b16] + Statistics
  [4607b0f0] + SuiteSparse
  [fa267f1f] + TOML
  [a4e569a6] + Tar
  [8dfed614] + Test
  [cf7118a7] + UUIDs
  [4ec0a83e] + Unicode
  [e66e0078] + CompilerSupportLibraries_jll
  [deac9b47] + LibCURL_jll
  [29816b5a] + LibSSH2_jll
  [c8ffd9c3] + MbedTLS_jll
  [14a3606d] + MozillaCACerts_jll
  [05823500] + OpenLibm_jll
  [83775a58] + Zlib_jll
  [8e850ede] + nghttp2_jll
  [3f19e933] + p7zip_jll

# 追加したパッケージが表示される
(pkgExample) pkg> status
      Status `~/projects/julia/Learn-Julia-Programming-from-Scratch-mokumoku/ch02/pkgExample/Project.toml`
  [31c24e10] Distributions v0.25.21

# Project.toml の内容
julia> run(pipeline(`cat Project.toml`))
name = "pkgExample"

[deps]
Distributions = "31c24e10-a181-5473-b8eb-7969acd0382f"
Process(`cat Project.toml`, ProcessExited(0))

```


### 2.11.3 プロジェクトの有効化
- `activate .` は REPL のみ可能
- `foo.jl` などのファイルでは, Julia コマンドに渡すときに `--project=@.` オプションを指定すると現在のディレクトリのプロジェクトを有効化する
- `--project` のみ記載しても同じ効果
- `JULIA_PROJECT` 環境変数に `@.` を指定しても同じ効果

```julia
# pkgExample2.jl
using Distributions
println("OK")
```

```shell
$ julia --project=@. pkgExample2.jl
OK

```


### 2.11.4 パッケージの作成
- Julia のパッケージは, 特定のディレクトリ構造を取る


```shell
./pkgExample/
├── LICENSE
├── Manifest.toml
├── Project.toml
├── README.md
├── docs
├── src
└── test

3 directories, 4 files
```


#### パッケージの作成


```julia
# パッケージのスケルトンを作成
(@v1.6) pkg> generate PkgExample2
  Generating  project PkgExample2:
    PkgExample2/Project.toml
    PkgExample2/src/PkgExample2.jl

# Project.toml の中身
julia> run(pipeline(`cat PkgExample2/Project.toml`))
name = "PkgExample2"
uuid = "229381da-56aa-44ad-aef9-07135bf10050"
authors = ["Yusuke Saito <ysaito8015@gmail.com>"]
version = "0.1.0"
Process(`cat PkgExample2/Project.toml`, ProcessExited(0))

# src/PkgExample.jl の中身
julia> run(pipeline(`cat PkgExample2/src/PkgExample2.jl`))
module PkgExample2

greet() = print("Hello World!")

end # module
Process(`cat PkgExample2/src/PkgExample2.jl`, ProcessExited(0))

# 生成したパッケージを利用する
julia> using PkgExample2
[ Info: Precompiling PkgExample2 [229381da-56aa-44ad-aef9-07135bf10050]

julia> PkgExample2.greet()
Hello World!
```


#### 生成したパッケージに変更を加える

```julia
# Primes パッケージの追加
(PkgExample2) pkg> add Primes
    Updating registry at `~/.julia/registries/General`
   Resolving package versions...
   Installed Primes ─ v0.5.0
    Updating `~/projects/julia/Learn-Julia-Programming-from-Scratch-mokumoku/ch02/PkgExample2/Project.toml`
  [27ebfcd6] + Primes v0.5.0
    Updating `~/projects/julia/Learn-Julia-Programming-from-Scratch-mokumoku/ch02/PkgExample2/Manifest.toml`
  [27ebfcd6] + Primes v0.5.0
Precompiling project...
  ✓ PkgExample2
  2 dependencies successfully precompiled in 2 seconds
  1 dependency precompiled but a different version is currently loaded. Restart julia to access the new version

```


```julia
# greet() 関数の変更
module PkgExample2

using Primes
greet() = print("Hello! Today's lucky prime number is $(rand(primes(100))).")

end # module
```


```julia
# 実行
julia> using PkgExample2
[ Info: Precompiling PkgExample2 [229381da-56aa-44ad-aef9-07135bf10050]

julia> PkgExample2.greet()
Hello! Today's lucky prime number is 73.
```
