{
    description = "Advent of code solutions";
    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-25.05";
    };

    outputs = { nixpkgs, systems, ... } @ inputs: let
        forEachSystem = nixpkgs.lib.genAttrs (import systems);
    in {
        devShells = forEachSystem (system: let
            pkgs = nixpkgs.legacyPackages.${system};
        in {
            default = pkgs.mkShell {
                packages = with pkgs; [ pkgs.linuxPackages_latest.perf aocd ];
                hardeningDisable = [ "all" ];

                nativeBuildInputs = with pkgs; [
                    clang
                    pkgconf
                    ninja
                    cmake
                    meson
                ];

                buildInputs = with pkgs; [
                    spdlog
                    nlohmann_json
                    cli11
                ];
            };
        });
    };
}