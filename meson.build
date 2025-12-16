project(
    'isenChef',
    'c'
)

src_file = files(
    'src/main.c',
    'src/args.c',
    'src/args_handlers.c',
    'src/file.c',
    'src/actions/toupper.c',
)

includes = include_directories('includes')

executable(
    'isenChef',
    src_file,
    include_directories: includes
)