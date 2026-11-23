{
    description = "Advent of code solutions";
    inputs = {
        nixpkgs.url = "github:nixos/nixpkgs/nixos-unstable";
    };

    outputs = { nixpkgs, systems, ... } @ inputs: let
        forEachSystem = nixpkgs.lib.genAttrs (import systems);
    in {
        devShells = forEachSystem (system: let
            pkgs = nixpkgs.legacyPackages.${system};
        in {
            default = pkgs.mkShell {
                packages = with pkgs; [
                    pkgs.linuxPackages_latest.perf
                    advent-of-code-data
                ];

                hardeningDisable = [ "all" ];
                nativeBuildInputs = with pkgs; [
                    clang-tools

                    llvmPackages_latest.lldb
                    llvmPackages_latest.libllvm
                    llvmPackages_latest.libcxx
                    llvmPackages_latest.clang

                    pkg-config
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