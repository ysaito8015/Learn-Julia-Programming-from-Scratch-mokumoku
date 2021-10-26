julia> ENV["PYTHON"]
"/home/ysaito/.pyenv/versions/anaconda3-2021.05/bin/python3.8"

julia> ENV["CONDA_JL_HOME"]
"/home/ysaito/.pyenv/versions/anaconda3-2021.05/"

(@v1.6) pkg> add PyCall
  Installing known registries into `~/.julia`
       Added registry `General` to `~/.julia/registries/General`
   Resolving package versions...
   Installed VersionParsing ─ v1.2.0
   Installed Conda ────────── v1.5.2
   Installed MacroTools ───── v0.5.8
   Installed PyCall ───────── v1.92.3
   Installed JSON ─────────── v0.21.2
   Installed Parsers ──────── v2.0.5
    Updating `~/.julia/environments/v1.6/Project.toml`
  [438e738f] + PyCall v1.92.3
    Updating `~/.julia/environments/v1.6/Manifest.toml`
  [8f4d0f93] + Conda v1.5.2
  [682c06a0] + JSON v0.21.2
  [1914dd2f] + MacroTools v0.5.8
  [69de0a69] + Parsers v2.0.5
  [438e738f] + PyCall v1.92.3
  [81def892] + VersionParsing v1.2.0
  [2a0f44e3] + Base64
  [ade2ca70] + Dates
  [8f399da3] + Libdl
  [37e2e46d] + LinearAlgebra
  [d6f4376e] + Markdown
  [a63ad114] + Mmap
  [de0858da] + Printf
  [9a3f8284] + Random
  [9e88b42a] + Serialization
  [4ec0a83e] + Unicode
    Building Conda ─→ `~/.julia/scratchspaces/44cfe95a-1eb2-52ea-b672-e2afdf69b78f/299304989a5e6473d985212c28928899c74e9421/build.log`
    Building PyCall → `~/.julia/scratchspaces/44cfe95a-1eb2-52ea-b672-e2afdf69b78f/169bb8ea6b1b143c5cf57df6d34d022a7b60c6db/build.log`
Precompiling project...
  2 dependencies successfully precompiled in 9 seconds (4 already precompiled)

(@v1.6) pkg> add PyPlot
    Updating registry at `~/.julia/registries/General`
   Resolving package versions...
   Installed FixedPointNumbers ─ v0.8.4
   Installed LaTeXStrings ────── v1.2.1
   Installed Reexport ────────── v1.2.2
   Installed PyPlot ──────────── v2.10.0
   Installed ColorTypes ──────── v0.11.0
   Installed Colors ──────────── v0.12.8
    Updating `~/.julia/environments/v1.6/Project.toml`
  [d330b81b] + PyPlot v2.10.0
    Updating `~/.julia/environments/v1.6/Manifest.toml`
  [3da002f7] + ColorTypes v0.11.0
  [5ae59095] + Colors v0.12.8
  [53c48c17] + FixedPointNumbers v0.8.4
  [b964fa9f] + LaTeXStrings v1.2.1
  [d330b81b] + PyPlot v2.10.0
  [189a3867] + Reexport v1.2.2
  [b77e0a4c] + InteractiveUtils
  [56ddb016] + Logging
  [6462fe0b] + Sockets
  [2f01184e] + SparseArrays
  [10745b16] + Statistics
  [8dfed614] + Test
Precompiling project...
  6 dependencies successfully precompiled in 21 seconds (6 already precompiled)

