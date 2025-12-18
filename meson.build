project(
    'isenChef',
    'c'
)

src_file = files(
    'src/main.c',
    'src/args.c',
    'src/args_handlers.c',
    'src/action_dispatcher.c',
    'src/file.c',
    'src/actions/toupper.c',
    'src/actions/tolower.c',
    'src/actions/tohex.c',
    'src/actions/tobase64.c',
    'src/actions/caesar.c',
)

includes = include_directories('includes')

executable(
    'isenChef',
    src_file,
    include_directories: includes
)