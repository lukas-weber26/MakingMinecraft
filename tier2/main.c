

int main() {
	//It seems like EBOs are actually pretty bad for this application. Sending the full set of triangles is a bit unpleasant but actually seems like a viable option. The problem with EBOs for this case is how textures work on these blocks. In the ideal case for an EBO, verteces have a texture attrib. Since textures usually wrap around an object made with lots of vertices this makes sense. The problem with my use case is that each block's texture has nothing to do with the neighbouring blocks texture, meaning that vertices are actually unique (not in space but in terms of their texture coordinate.) 
	
	//It now seems like the way to go is to have each cube store the full 36 triangles, each of which contains an appropriate texture coordinate. This is ok as long as there is a function to create the mess and as long as only the parts that are changes are actually updated by the CPU.
	
	//
}
