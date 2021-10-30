```julia
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
```

-----------------------------------------------------------

```julia
julia> ENV["PYTHON"]
"/home/pi/.pyenv/shims/python3"

julia> ENV["CONDA_JL_HOME"]
""
julia> using Pkg

julia> Pkg.build("PyCall")
    Building Conda ─→ `~/.julia/scratchspaces/44cfe95a-1eb2-52ea-b672-e2afdf69b78f/299304989a5e6473d985212c28928899c74e9421/build.log`
    Building PyCall → `~/.julia/scratchspaces/44cfe95a-1eb2-52ea-b672-e2afdf69b78f/169bb8ea6b1b143c5cf57df6d34d022a7b60c6db/build.log`
ERROR: Error building `PyCall`:
ERROR: LoadError: ArgumentError: Path to conda environment is not valid:
Stacktrace:
 [1] prefix(path::String)
   @ Conda ~/.julia/packages/Conda/sNGum/src/Conda.jl:41
 [2] top-level scope
   @ ~/.julia/packages/Conda/sNGum/src/Conda.jl:46
 [3] include
   @ ./Base.jl:386 [inlined]
 [4] include_package_for_output(pkg::Base.PkgId, input::String, depot_path::Vector{String}, dl_load_path::Vector{String}, load_path::Vector{String}, concrete_deps::Vector{Pair{Base.PkgId, UInt64}}, source::String)
   @ Base ./loading.jl:1235
 [5] top-level scope
   @ none:1
 [6] eval
   @ ./boot.jl:360 [inlined]
 [7] eval(x::Expr)
   @ Base.MainInclude ./client.jl:446
 [8] top-level scope
   @ none:1
in expression starting at /home/pi/.julia/packages/Conda/sNGum/src/Conda.jl:1
ERROR: LoadError: Failed to precompile Conda [8f4d0f93-b110-5947-807f-2305c1781a2d] to /home/pi/.julia/compiled/v1.6/Conda/jl_3UbDhr.
Stacktrace:
 [1] error(s::String)
   @ Base ./error.jl:33
 [2] compilecache(pkg::Base.PkgId, path::String, internal_stderr::IOContext{IOStream}, internal_stdout::IOContext{IOStream}, ignore_loaded_modules::Bool)
   @ Base ./loading.jl:1385
 [3] compilecache(pkg::Base.PkgId, path::String)
   @ Base ./loading.jl:1329
 [4] _require(pkg::Base.PkgId)
   @ Base ./loading.jl:1043
 [5] require(uuidkey::Base.PkgId)
   @ Base ./loading.jl:936
 [6] require(into::Module, mod::Symbol)
   @ Base ./loading.jl:923
 [7] include(fname::String)
   @ Base.MainInclude ./client.jl:444
 [8] top-level scope
   @ none:5
in expression starting at /home/pi/.julia/packages/PyCall/BD546/deps/build.jl:9
Stacktrace:
  [1] pkgerror(msg::String)
    @ Pkg.Types /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/Types.jl:55
  [2] (::Pkg.Operations.var"#82#87"{Bool, Pkg.Types.Context, String, Pkg.Types.PackageSpec})()
    @ Pkg.Operations /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/Operations.jl:1048
  [3] withenv(::Pkg.Operations.var"#82#87"{Bool, Pkg.Types.Context, String, Pkg.Types.PackageSpec}, ::Pair{String, String}, ::Vararg{Pair{String, B} where B, N} where N)
    @ Base ./env.jl:161
  [4] (::Pkg.Operations.var"#109#113"{String, Pkg.Operations.var"#82#87"{Bool, Pkg.Types.Context, String, Pkg.Types.PackageSpec}, Pkg.Types.PackageSpec})()
    @ Pkg.Operations /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/Operations.jl:1546
  [5] with_temp_env(fn::Pkg.Operations.var"#109#113"{String, Pkg.Operations.var"#82#87"{Bool, Pkg.Types.Context, String, Pkg.Types.PackageSpec}, Pkg.Types.PackageSpec}, temp_env::String)
    @ Pkg.Operations /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/Operations.jl:1448
  [6] (::Pkg.Operations.var"#108#112"{Pkg.Operations.var"#82#87"{Bool, Pkg.Types.Context, String, Pkg.Types.PackageSpec}, Pkg.Types.Context, Pkg.Types.PackageSpec, String, Pkg.Types.Project, String})(tmp::String)
    @ Pkg.Operations /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/Operations.jl:1521
  [7] mktempdir(fn::Pkg.Operations.var"#108#112"{Pkg.Operations.var"#82#87"{Bool, Pkg.Types.Context, String, Pkg.Types.PackageSpec}, Pkg.Types.Context, Pkg.Types.PackageSpec, String, Pkg.Types.Project, String}, parent::String; prefix::String)
    @ Base.Filesystem ./file.jl:729
  [8] mktempdir(fn::Function, parent::String) (repeats 2 times)
    @ Base.Filesystem ./file.jl:727
  [9] sandbox(fn::Function, ctx::Pkg.Types.Context, target::Pkg.Types.PackageSpec, target_path::String, sandbox_path::String, sandbox_project_override::Pkg.Types.Project)
    @ Pkg.Operations /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/Operations.jl:1487
 [10] build_versions(ctx::Pkg.Types.Context, uuids::Vector{Base.UUID}; verbose::Bool)
    @ Pkg.Operations /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/Operations.jl:1029
 [11] build(ctx::Pkg.Types.Context, pkgs::Vector{Pkg.Types.PackageSpec}, verbose::Bool)
    @ Pkg.Operations /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/Operations.jl:910
 [12] build(ctx::Pkg.Types.Context, pkgs::Vector{Pkg.Types.PackageSpec}; verbose::Bool, kwargs::Base.Iterators.Pairs{Symbol, Base.TTY, Tuple{Symbol}, NamedTuple{(:io,), Tuple{Base.TTY}}})
    @ Pkg.API /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/API.jl:900
 [13] build(pkgs::Vector{Pkg.Types.PackageSpec}; io::Base.TTY, kwargs::Base.Iterators.Pairs{Union{}, Union{}, Tuple{}, NamedTuple{(), Tuple{}}})
    @ Pkg.API /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/API.jl:80
 [14] build(pkgs::Vector{Pkg.Types.PackageSpec})
    @ Pkg.API /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/API.jl:78
 [15] #build#71
    @ /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/API.jl:76 [inlined]
 [16] build
    @ /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/API.jl:76 [inlined]
 [17] #build#70
    @ /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/API.jl:75 [inlined]
 [18] build(pkg::String)
    @ Pkg.API /buildworker/worker/package_linuxarmv7l/build/usr/share/julia/stdlib/v1.6/Pkg/src/API.jl:75
 [19] top-level scope
    @ REPL[2]:1

```


