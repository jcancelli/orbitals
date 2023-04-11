<script lang="ts">
	export let height: number;
	export let width: number;
</script>

<canvas
	{width}
	{height}
	style:width={width + "px"}
	style:height={height + "px"}
>
	<div class="fixed top-0 left-0 w-screen h-screen flex flex-col items-center justify-center">
		<img
			src="https://media.tenor.com/vuE2MOlHrIQAAAAC/stupid-retarded.gif"
			alt="Braindead Wojak"
		/>
		<h1 class="text-2xl">Woops... Looks like Javascript is not enabled on your browser!</h1>
	</div>
</canvas>
