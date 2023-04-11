<script lang="ts">
	import Viewport from "$lib/components/Viewport.svelte";
	import { onMount, onDestroy } from "svelte";
	import "../app.css";

	let viewportWidth: number;
	let viewportHeight: number;

	onMount(() => {
		window.addEventListener("resize", onWindowResize);
		onWindowResize(); // init viewport size
	});

	onDestroy(() => {
		window.removeEventListener("resize", onWindowResize);
	});

	function onWindowResize(): void {
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
