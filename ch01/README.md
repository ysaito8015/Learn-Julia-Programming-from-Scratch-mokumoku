# 1.1 Julia 概要

# 1.2 インストール
- https://julialang.org
- v1.6.2
	- x86_64
	    - https://julialang-s3.julialang.org/bin/linux/x64/1.6/julia-1.6.2-linux-x86_64.tar.gz
	- arm 32bit 版
	    - https://julialang-s3.julialang.org/bin/linux/armv7l/1.6/julia-1.6.2-linux-armv7l.tar.gz

## 1.2.1 REPL
- `ans` という変数に直前の計算結果が格納される
- julia の REPL
    - Julia モード
        - `julia>` と表示されている状態
    - ヘルプモード
        - コマンドのヘルプを表示する
        - `julia>` の状態で `?` キーを押す
            - `+` と入力してエンターでヘルプ表示
        - Julia モードに復帰するには `BS`
    - パッケージモード
        - パッケージのインストール
        - `julia>` の状態で `]` キーを押す
            - `add Example` と入力してエンターで `Example.jl` のインストール
        - Julia モードに復帰するには `BS`
    - シェルモード
    - サーチモード

## 1.2.2 Jupyter Notebook
- IJulia.jl パッケージのインストール
    - `add IJulia`
- 使い方

```
using IJulia
notebook()
```

## 1.2.3 エディタと IDE
- JuliaEditorSupport
    - https://github.coom/JuliaEditorSupport
- シェルから `*.jl` ファイルを実行する
    - `$ julia sample.jl arg1 arg2`

# 1.3 Julia の情報

## 1.3.1 Julia 公式ページ
- https://julilang.org

## 1.3.2 Julia のソースコード
- https://github.com/JuliaLang/julia

## 1.3.3 Julia Discourse
- https://discourse.julialang.org/

## 1.3.4 JuliaCon

## 1.3.5 JuliaTokyo
