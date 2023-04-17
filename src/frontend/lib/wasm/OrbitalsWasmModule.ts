// Type declarations for the cpp stuff (classes, functions, etc) exported by the emscripten wasm module
// Must be updated manually

export type OrbitalsWasmModule = {
	Orbitals: new (viewportId: string) => Orbitals
} & EmscriptenModule

export abstract class Orbitals {
	abstract setViewportWidth(width: number): void;
	abstract setViewportHeight(height: number): void;
}

export default OrbitalsWasmModule