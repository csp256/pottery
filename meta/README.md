This folder contains "meta-templates", i.e. templates that are used to generate parts of Pottery's templates. Many of Pottery's `macros` and `unmacros` headers contain sections that say `AUTOGENERATED`. These are generated from the meta-templates here. The generator replaces these sections in-place in the headers.

These are largely used for forwarding user configuration. For example when you instantiate a [vector](../include/pottery/vector/), you configure lifecycle functions on the vector template, like `POTTERY_VECTOR_LIFECYCLE_DESTROY`. But vector uses the [lifecycle](../include/pottery/lifecycle/) template to actually implement this, so it needs to forward along the configuration to `POTTERY_LIFECYCLE_DESTROY`. Since these macros are the same across many containers, they are generated from [`lifecycle/forward.m.h`](lifecycle/forward.m.h).

The partially generated headers are committed to the repository. This is unconventional of course, as generated code should generally never be committed. But there are good reasons to do this for Pottery:

- The `macros` and `unmacros` headers are only partially generated; much of them are hand-written. I've tried splitting the generated portions into their own headers and there ends up being just way too many header files. There are already too many headers per template algorithm/container as it is. This is as simple as I can make it (short of abandoning generation and writing the macros by hand.)

- Having the generated code in the repository means the repository can be used as-is without needing to perform a code generation step. This way we can write the generator in any language and not require that users of the library be able to run it. You only need to run the generator if you change the meta-templates or change some template's use of them.

The latter point makes Pottery trivially usable as a header-only library. You can just take a tarball from any commit of Pottery, dump it onto your include path and start using it. See the [integration documentation](../docs/integration.md) to see how easy this is in practice.

The unit test suite and fuzz testing scripts regenerate all headers automatically, so you can just run them as normal while making changes to Pottery. If the meta-template generator script notices any changes during CI builds, it will fail. This ensures that all meta-templates are correctly generated in any commit that passed CI.
