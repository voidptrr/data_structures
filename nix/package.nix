{
  lib,
  cmake,
  stdenv,
  systems,
  clang,
}:
stdenv.mkDerivation {
  pname = "data_structures";
  version = "0.1.0-dev";

  src = lib.fileset.toSource {
    root = ../.;
    fileset = lib.fileset.intersection (lib.fileset.fromSource (lib.sources.cleanSource ../.)) (
      lib.fileset.unions [
        ../src
        ../CMakeLists.txt
      ]
    );
  };

  nativeBuildInputs = [cmake clang];

  cmakeFlags = [
    "-DCMAKE_C_COMPILER=${clang}/bin/clang"
  ];

  meta = {
    homepage = "https://github.com/voidptrr/data_structures";
    license = lib.licenses.mit;
    platforms = systems;
    mainProgram = "data_structures";
  };
}
