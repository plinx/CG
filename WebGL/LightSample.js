/* 
 * @requires Vector3, Color
 */

LightSample = function(L, EL) { this.L = L; this.EL = EL; };

LightSample.zero = new LightSample(Vector3.zero, Color.black);
