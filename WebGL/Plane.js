/* 
 * @requires Vector3
 * @requires IntersectResult
 */
 
Plane = function(normal, d) { this.normal = normal; this.d = d; };

Plane.prototype = {
    copy : function() { return new plane(this.normal.copy(), this.d); },

    initialize : function() {
        this.position = this.normal.multiply(this.d);
    },
    
    intersect : function(ray) {
        var a = ray.direction.dot(this.normal);
        if (a >= 0)
            return IntersectResult.noHit;

        var b = this.normal.dot(ray.origin.subtract(this.position));
        var result = new IntersectResult();
        result.geometry = this;
        result.distance = -b / a;
        result.position = ray.getPoint(result.distance);
        result.normal = this.normal;
        return result;
    }
};
