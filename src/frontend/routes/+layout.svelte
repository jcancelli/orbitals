<script lang="ts">
	import "../app.css";
	import Viewport from "$lib/components/Viewport.svelte";
	import loadWasmModule from "$lib/wasm.mjs";
	import { onMount, onDestroy } from "svelte";

	let viewportWidth: number;
	let viewportHeight: number;

	onMount(async () => {
		window.addEventListener("resize", resizeViewport);
		resizeViewport();

		const moduleOverrides: Partial<EmscriptenModule> = {
			locateFile: (path: string, prefix: string) => {
				return path;
			}
		};

		const wasmModule: EmscriptenModule = await loadWasmModule(moduleOverrides);
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
		width={viewportWidth}
		height={viewportHeight}
	/>
</div>
<slot />
