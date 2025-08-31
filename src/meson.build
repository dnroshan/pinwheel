pinwheel_sources = [
  'main.c',
  'pw-application.c',
  'pw-window.c',
  'pw-canvas.c',
]

pinwheel_deps = [
  dependency('gtk4'),
  dependency('libadwaita-1', version: '>= 1.4'),
]

pinwheel_sources += gnome.compile_resources('pw-resources',
  'pw.gresource.xml',
  c_name: 'pw'
)

executable('pinwheel', pinwheel_sources,
  dependencies: pinwheel_deps,
       install: true,
)