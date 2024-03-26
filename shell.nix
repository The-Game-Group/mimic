with import <nixpkgs> {};

stdenv.mkDerivation {
    name = "mimic";
    buildInputs = [ bazel clang-tools pre-commit ];

    shellHook = ''
        pre-commit install
    '';
}