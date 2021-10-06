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

```
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

```
# 書籍の例のように BigInt 型にならないですね...
julia> x = 123567890123456789012345678901234567890
123567890123456789012345678901234567890

julia> x * x
16709914794736288363445475719704024132

julia> typeof(ans)
Int128
```

```
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

```
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
|x || y    | short-circuiting or           |                                        |
|~x        | bitwise not                   |                                        |
|x & y     | bitwise and                   |                                        |
|x | y     | bitwise or                    |                                        |
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
