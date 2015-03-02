var VSHADER_SOURCE = 
	"void main() {\n" +
	"	gl_Position = vec4(0.0, 0.0, 0.0, 1.0);\n" +
	"	gl_PointSize = 10.0;\n" +
	"}\n";

var FSHADER_SOURCE = 
	"void main() {\n" +
	"	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);\n" +
	"}\n";


function main()
{
	var canvas = document.getElementById('cbox');
	var ctx = canvas.getContext("2d");
}