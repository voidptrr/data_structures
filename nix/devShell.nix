{
  clang-tools,
  alejandra,
  cmake,
  ninja,
  mkShell,
}:
mkShell {
  name = "data_structures_shell";
  packages = [cmake ninja clang-tools alejandra];
}
