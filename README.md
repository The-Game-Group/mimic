# Mimic

Mimic is a game engine of some sort that will provide a basis for Simdustry.

## Bazel

To build:
```bash
$ bazel build :mimic
```

To run:
```bash
$ bazel run :mimic
```

To test:
```bash
$ bazel test test:all
```

Rebuild `compile_commands.json`:
```bash
$ bazel run @hedron_compile_commands//:refresh_all
```