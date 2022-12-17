class Vector{
	public:
		double x, y;

		Vector(){
			this->x = 0;
			this->y = 0;
		}

		Vector(double x, double y){
			this->x = x;
			this->y = y;
		}

		void sum(Vector v){
			this->x += v.x;
			this->y += v.y;
		}

		void sub(Vector v){
			this->x -= v.x;
			this->y -= v.y;
		}

		void div(double value){
			this->x /= value;
			this->y /= value;
		}

		void mul(double value){
			this->x *= value;
			this->y *= value;
		}

		double angle(){
			return atan2(this->y, this->x);
		}

		double mag(){
			return sqrt(pow(this->x, 2) + pow(this->y, 2));
		}

		void limit(double limit){
			
			double mag = this->mag();
			
			if(mag != 0 && mag > limit){
				this->x *= limit / mag;
				this->y *= limit / mag; 
			}
		}

		void normalize(){
			double mag = this->mag();

			if(mag != 0){
				this->x /=  mag;
				this->y /=  mag; 
			}
		}

		double dot(Vector v){
			return this->x * v.x + this->y * v.y;		
		}

		static Vector sub(Vector v1, Vector v2){
			return Vector(v1.x - v2.x, v1.y - v2.y);
		}

		static double distance(Vector v1, Vector v2){
			return sqrt(pow(v1.x - v2.x, 2) + pow(v1.y - v2.y, 2));
		}

		static double angle_between(Vector v1, Vector v2){
			return acos(v1.dot(v2) / (v1.mag() * v2.mag()));
		}
};
