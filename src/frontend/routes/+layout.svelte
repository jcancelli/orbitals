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
		console.log("----------------------------------------------------------------------------");
		const initStartTime = Date.now();
		window.addEventListener("resize", resizeViewport);
		resizeViewport();

		const moduleOverrides: Partial<EmscriptenModule> = {
			locateFile: (path: string, prefix: string) => {
				return base + "/" + path;
			}
		};
		wasmModule = await loadWasmModule(moduleOverrides);
		console.log("[js] - wasm module loaded");
		orbitals = await new wasmModule.Orbitals();
		console.log("[js] - app object instantiated");
		orbitals.start();
		console.log("[js] - app started");
		console.log("[js] - init time " + (Date.now() - initStartTime) + "ms");
	});

	onDestroy(() => {
		window.removeEventListener("resize", resizeViewport);
	});

	function resizeViewport(): void {
		viewportWidth = window.innerWidth;
		viewportHeight = window.innerHeight;
	}
</script>

<div class="fixed top-0 left-0 w-screen h-screen flex items-center justify-center">
	<Viewport
		id="viewport"
		width={viewportWidth}
		height={viewportHeight}
	/>
</div>
<slot />
