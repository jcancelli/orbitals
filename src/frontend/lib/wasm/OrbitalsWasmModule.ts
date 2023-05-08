// Type declarations for the cpp stuff (classes, functions, etc) exported by the emscripten wasm module
// Must be updated manually

export type OrbitalsWasmModule = {
	Orbitals: new (viewportId: string) => Orbitals
} & EmscriptenModule

export abstract class Orbitals {
	abstract start(): void;
	abstract stop(): void;
}

export default OrbitalsWasmModule