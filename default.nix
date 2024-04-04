with import <nixpkgs> { };

let
  graphics_dependencies = [
    libGL
    xorg.libX11
    xorg.libfontenc
    xorg.libICE
    xorg.libSM
    xorg.libXau
    xorg.libXaw
    xorg.libXcomposite
    xorg.libXcursor
    xorg.libXdamage
    xorg.libXdmcp
    xorg.libXext
    xorg.libXi
    xorg.libXinerama
    xorg.libxkbfile
    xorg.libXpm
    xorg.libXrandr
    xorg.libXres
    xorg.libXScrnSaver
    xorg.libXtst
    xorg.libXv
    xorg.libXxf86vm
    xorg.xcbutilwm
    xorg.xcbutilimage
    xorg.xcbutilkeysyms
    xorg.xcbutilrenderutil
    xorg.xcbutil
    xcb-util-cursor

    wayland.dev
    libxkbcommon
  ];
in stdenv.mkDerivation {
  name = "mimic";
  buildInputs = [
    clang-tools
    cmake
    git
    ninja
    pre-commit
    pkg-config

    libuuid
    expat
    bison
    flex
    zlib
    libxml2
    libiconv
    libffi
    python311Packages.jinja2

    # glfw # x11
    glfw-wayland
  ] ++ graphics_dependencies;

  #shellHook = ''
  #  pre-commit install
  #'';
}
