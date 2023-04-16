<script lang="ts">
	import "../app.css";
	import Viewport from "$lib/components/Viewport.svelte";
	import loadWasmModule from "$lib/wasm/wasm.mjs";
	import { onMount, onDestroy } from "svelte";
	import { base } from "$app/paths";
	import type OrbitalsWasmModule from "$lib/wasm/OrbitalsWasmModule";
	import type { Orbitals } from "$lib/wasm/OrbitalsWasmModule";

	let viewportWidth: number;
	let viewportHeight: number;

	let wasmModule: OrbitalsWasmModule;
	let orbitals: Orbitals;

	onMount(async () => {
		window.addEventListener("resize", resizeViewport);

		const moduleOverrides: Partial<EmscriptenModule> = {
			locateFile: (path: string, prefix: string) => {
				return base + "/" + path;
			}
		};
		wasmModule = await loadWasmModule(moduleOverrides);
		orbitals = new wasmModule.Orbitals();

		resizeViewport();
	});

	onDestroy(() => {
		window.removeEventListener("resize", resizeViewport);
	});

	function resizeViewport(): void {
		viewportWidth = window.innerWidth;
		viewportHeight = window.innerHeight;
		orbitals.setViewportWidth(viewportWidth);
		orbitals.setViewportHeight(viewportHeight);
	}
</script>

<div class="fixed top-0 left-0 w-screen h-screen flex items-center justify-center">
	<Viewport
		width={viewportWidth}
		height={viewportHeight}
	/>
</div>
<slot />
