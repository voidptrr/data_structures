{
  description = "data_structures";

  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixpkgs-unstable";
    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = {
    nixpkgs,
    flake-utils,
    ...
  }: let
    systems = [
      "x86_64-linux"
      "x86_64-darwin"
      "aarch64-linux"
      "aarch64-darwin"
    ];
  in
    flake-utils.lib.eachSystem systems (
      system: let
        pkgs = nixpkgs.legacyPackages.${system};
      in rec {
        devShells.default = pkgs.callPackage ./nix/devShell.nix {};
        packages.default = pkgs.callPackage ./nix/package.nix {inherit systems;};

        apps = rec {
          default = data_structures;
          data_structures = flake-utils.lib.mkApp {drv = packages.default;};
        };

        checks = import ./nix/checks.nix {inherit pkgs;};
        formatter = pkgs.alejandra;
      }
    );
}
