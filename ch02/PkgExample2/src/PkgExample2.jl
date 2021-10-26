module PkgExample2

using Primes
greet() = print("Hello! Today's lucky prime number is $(rand(primes(100))).")

end # module
