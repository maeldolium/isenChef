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
    'src/errors.c',
    'src/actions/toupper.c',
    'src/actions/tolower.c',
    'src/actions/caesar.c',
    'src/actions/rc4.c',
    'src/actions/xor.c',
    'src/format_dispatcher.c',
    'src/formats/hex.c',
    'src/formats/base64.c',
)

includes = include_directories('includes')

executable(
    'isenChef',
    src_file,
    include_directories: includes
)