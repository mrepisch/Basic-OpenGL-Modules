

in vec2 TexCoords;
uniform sampler2d atexture;
void main()
{
	FragColor = texture(atexture, TexCoords);
}  
