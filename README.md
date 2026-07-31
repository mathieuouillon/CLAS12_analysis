# skim_for_RGD

A fast C++ **HIPO skimmer** for CLAS12 Run Group D. It reads pass1 reconstructed DST files and writes much smaller per-run skims containing only **electron-triggered events** with a reduced set of banks — the input for the downstream RG-D analyses (timelines, transparency, etc.).

For each run under `/cache/clas12/rg-d/production/pass1/recon/<target>/dst/recon/`, it keeps events where `REC::Particle` has a "good electron" (`pid == 11`, `status < 0`, `-10 < chi2pid < 10`), and for those events writes a whitelist of banks (`RUN::config`, `RUN::scaler`, `REC::Event`, `REC::Particle`, `REC::Calorimeter`, `REC::ForwardTagger`, `REC::Scintillator`, `REC::Track`, `REC::CovMat`, `REC::Traj`, `REC::Cherenkov`, `RUN::rf`) to `skim_run_<run>.hipo` under `/volatile/clas12/ouillon/skim_pass1_RGD/<target>`.

## Build & run

**C++ (meson/ninja)**; depends on the `hipo4` library via a git-submodule meson subproject.

```bash
git submodule update --init      # fetch subprojects/hipo (first time)
meson setup build
ninja -C build
./build/skim_rgd                 # takes NO args — paths/target/threads are hardcoded in src/main.cpp
```

Input paths, the target (currently `CuSn`), the output dir, and the 40-thread count are all hardcoded in `src/main.cpp` — edit there to change targets.

## Key files

- `src/main.cpp` — entry point; enumerates run folders per target and dispatches via `multi_thread_reader(..., 40)`.
- `src/skimer/Reader.cpp` — the skim logic (electron filter + bank whitelist + HIPO writer).
- `include/skimer/Reader.hpp` — `skimer::Reader` functor (`operator()(run)`).
- `include/thread_pool/{multi_thread.hpp,BS_thread_pool*.hpp}` — vendored BS::thread_pool + the per-run parallel driver.
- `meson.build` — build definition; `subproject('hipo')` + `dependency('hipo4')`.
- `subprojects/hipo/` — HIPO library as a **git submodule** (build dependency, keep).

## Notes

- Cleaned up (2026-07-20): removed `build/` and the `.cache/clangd` index. Rebuild with the commands above.
- The meson project was renamed from the template default `project_template` to **`skim_rgd`** (the built executable name follows the project name).
