{pkgs, ...}: {
  format-check =
    pkgs.runCommand "format-check" {
      src = ../.;
      nativeBuildInputs = with pkgs; [clang-tools alejandra];
    } ''
      alejandra --check $src
      find $src/src -type f \( -name "*.c" -o -name "*.h" \) \
        -exec clang-format --dry-run --Werror {} +

      touch $out
    '';

  #lint-check =
  # pkgs.runCommand "lint-check" {
  #  src = ../.;
  # nativeBuildInputs = with pkgs; [clang-tools];
  #} ''
  # clang-tidy --config-file=$src/.clang-tidy $src/src/*.c -- -I$src/src/include

  #touch $out
  #'';
}
