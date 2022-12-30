{ pkgs ? import <nixpkgs> {} }:
  pkgs.mkShell {
    nativeBuildInputs = [ pkgs.SDL2 pkgs.cairo pkgs.clojure pkgs.gdb ];
}
