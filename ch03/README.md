# 3. Julia ライブラリの使い方
## 3.1 線形代数
- 多次元配列
- `Array` 型を使った線形代数の演算
- `LinearAlgebra` モジュールを利用する


### 3.1.1 ベクトルの演算

```julia
julia> using LinearAlgebra

# 内積
julia> dot([1 2 3], [4 5 6])
32

# クロス積
# [1 2 3] とかくと, 2d 行ベクトル
# [1, 2, 3] とかくと, 1d 列ベクトル
julia> cross([0 1 0], [0 0 1])
ERROR: MethodError: no method matching cross(::Matrix{Int64}, ::Matrix{Int64})

You might have used a 2d row vector where a 1d column vector was required.
Note the difference between 1d column vector [1,2,3] and 2d row vector [1 2 3].
You can convert to a column vector with the vec() function.
Stacktrace:
 [1] top-level scope
   @ REPL[3]:1

julia> cross([0, 1, 0], [0, 0, 1])
3-element Vector{Int64}:
 1
 0
 0

julia> v = [- 1, 2, 3]
3-element Vector{Int64}:
 -1
  2
  3

# L¹ノルム
julia> norm(v, 1)
6.0

# L²ノルム
julia> norm(v, 2)
3.7416573867739413

# L∞ノルム
julia> norm(v, Inf)
3.0

# L1 ノルムで正規化
julia> normalize(v, 1)
3-element Vector{Float64}:
 -0.16666666666666666
  0.3333333333333333
  0.5

# L2 ノルムで正規化
julia> normalize(v, 2)
3-element Vector{Float64}:
 -0.2672612419124244
  0.5345224838248488
  0.8017837257372732

```


### 3.1.2 行列の演算

```julia
julia> A = [1 2 3; 4 1 6; 7 8 1]
3×3 Matrix{Int64}:
 1  2  3
 4  1  6
 7  8  1

julia> tr(A)
3

julia> det(A)
104.0

julia> inv(A)
3×3 Matrix{Float64}:
 -0.451923   0.211538    0.0865385
  0.365385  -0.192308    0.0576923
  0.240385   0.0576923  -0.0673077

```


### 3.1.3 行列の種類
- `Symmetric()` 関数の2つ目の引数
  - `:L` であれば行列 A の下三角行列に基づく対称行列を作成
  - `:U` であれば行列 A の上三角行列の基づく対称行列を作成する
- Julia でサポートされている特殊な種類の行列


| 型              | 概要             |
|-----------------|------------------|
| Symmetric       | 対称行列         |
| Hermitian       | エルミート行列   |
| UpperTriangular | 上三角行列       |
| LowerTriangular | 下三角行列       |
| Tridiagonal     | 三重対角行列     |
| SymTridiagonal  | 対称三重対角行列 |
| Bidiagonal      | 二重対角行列     |
| Diagonal        | 対角行列         |


```julia
# 行列を作成
julia> A = rand(3,3)
3×3 Matrix{Float64}:
 0.846013  0.595703  0.738091
 0.140951  0.837121  0.0848668
 0.14217   0.863517  0.929818

# 対称行列を作成
julia> Symmetric(A)
3×3 Symmetric{Float64, Matrix{Float64}}:
 0.846013  0.595703   0.738091
 0.595703  0.837121   0.0848668
 0.738091  0.0848668  0.929818

# 下三角行列に基づく対称行列
julia> Symmetric(A, :L)
3×3 Symmetric{Float64, Matrix{Float64}}:
 0.846013  0.140951  0.14217
 0.140951  0.837121  0.863517
 0.14217   0.863517  0.929818

julia> issymmetric(Symmetric(A))
true

# 上三角行列の作成
julia> A = [1 2 3; 4 5 6; 7 8 9]
3×3 Matrix{Int64}:
 1  2  3
 4  5  6
 7  8  9

julia> UpperTriangular(A)
3×3 UpperTriangular{Int64, Matrix{Int64}}:
 1  2  3
 ⋅  5  6
 ⋅  ⋅  9

```


### 3.1. 行列分解
- Cholesky 分解
- LU 分解
- `cholesky!` などの `!` がついた関数はもとの変数の内容を破壊的に変更する
- 主要な行列分解の関数


| 関数       | 概要            |
|------------|-----------------|
| cholesky   | Cholesky 分解   |
| lu         | LU 分解         |
| qr         | QR 分解         |
| hessenberg | Hessenberg 分解 |
| eigen      | スペクトル分解  |
| svd        | 特異値分解      |


```julia
# 特異値分解
julia> A = rand(Float32, 4, 3)
4×3 Matrix{Float32}:
 0.65983   0.297849  0.894127
 0.342928  0.167246  0.554292
 0.388314  0.174445  0.671168
 0.531684  0.342974  0.988402

julia> F = svd(A)
SVD{Float32, Float32, Matrix{Float32}}
U factor:
4×3 Matrix{Float32}:
 -0.590802   0.753052     0.231404
 -0.346558   0.00665936  -0.220429
 -0.408761  -0.14826     -0.827834
 -0.60313   -0.641005     0.461035
singular values:
3-element Vector{Float32}:
 1.94146
 0.11710294
 0.04823454
Vt factor:
3×3 Matrix{Float32}:
 -0.508934   -0.263768  -0.819398
  0.860661   -0.173372  -0.478754
  0.0157812   0.948877  -0.31525

julia> typeof(F)
SVD{Float32, Float32, Matrix{Float32}}

julia> F.S
3-element Vector{Float32}:
 1.94146
 0.11710294
 0.04823454

```


### 3.1.5 BLAS, Basic Linear Algebra Subprograms
- 線形代数の演算に関する標準的な API 規格
- `LinearALgebra.BLAS` モジュール

#### `gemv` 関数
- 行列とベクトルの積を計算する
    - `y = α* A * x + β* y`
- 引数
    - `'T'`, 転置


```julia
julia> using LinearAlgebra.BLAS

julia> A = [1.0 4.0; 2.0 5.0; 3.0 6.0]
3×2 Matrix{Float64}:
 1.0  4.0
 2.0  5.0
 3.0  6.0

julia> x = [1.0, 2.0, 3.0]
3-element Vector{Float64}:
 1.0
 2.0
 3.0

julia> y = [0.0, 0.0]
2-element Vector{Float64}:
 0.0
 0.0

julia> BLAS.gemv!('T', 1.0, A, x, 1.0, y)
2-element Vector{Float64}:
 14.0
 32.0

```


#### `gemm` 関数
- 行列同士の掛け算
- `C = α * A * B + β * C` (A, B, C は行列)


```julia
julia> using LinearAlgebra.BLAS

julia> A = reshape([1.0, 2.0, 3.0, 4.0, 5.0, 6.0], 3, 2)
3×2 Matrix{Float64}:
 1.0  4.0
 2.0  5.0
 3.0  6.0

julia> B = copy(A)
3×2 Matrix{Float64}:
 1.0  4.0
 2.0  5.0
 3.0  6.0

julia> C = zeros(3, 3)
3×3 Matrix{Float64}:
 0.0  0.0  0.0
 0.0  0.0  0.0
 0.0  0.0  0.0

julia> BLAS.gemm!('N', 'T', 1.0, A, B, 1.0, C)
3×3 Matrix{Float64}:
 17.0  22.0  27.0
 22.0  29.0  36.0
 27.0  36.0  45.0

```
