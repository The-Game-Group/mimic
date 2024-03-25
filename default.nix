with import <nixpkgs> {};
stdenv.mkDerivation {
    name = "tgg-engine";
    buildInputs = [ bazel clang-tools conan ];
}