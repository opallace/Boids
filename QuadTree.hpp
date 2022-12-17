class Rectangle{
	public:
		double x, y, w, h;

		Rectangle(){}

		Rectangle(double x, double y, double w, double h){
			this->x = x;
			this->y = y;
			this->w = w;
			this->h = h;
		}

		bool contains(Boid *boid){
			return (
				boid->position.x >= this->x - this->w &&
				boid->position.x <= this->x + this->w &&
				boid->position.y >= this->y - this->h &&
				boid->position.y <= this->y + this->h
			);
		}

		bool intersects(Rectangle *range){
			return !(
				range->x - range->w > this->x + this->w ||
			    range->x + range->w < this->x - this->w ||
			    range->y - range->h > this->y + this->h ||
			    range->y + range->h < this->y - this->h
			);
		}

		~Rectangle(){}
};

class QuadTree{
	public:
		Rectangle boundary;

		QuadTree *northeast;
		QuadTree *northwest;
		QuadTree *southeast;
		QuadTree *southwest;

		vector<Boid*> boids;
		
		int capacity;
		bool divided;

		QuadTree(){}

		QuadTree(Rectangle boundary, int capacity){
			this->boundary = boundary;
			this->capacity = capacity;
			this->divided  = false;
			this->northeast = NULL;
			this->northwest = NULL;
			this->southeast = NULL;
			this->southwest = NULL;
		}

		void subdivide(){
			double x = this->boundary.x;
			double y = this->boundary.y;
			double w = this->boundary.w / 2.0;
			double h = this->boundary.h / 2.0;

			this->northeast = new QuadTree(Rectangle(x + w, y - h, w, h), this->capacity);
			this->northwest = new QuadTree(Rectangle(x - w, y - h, w, h), this->capacity);
			this->southeast = new QuadTree(Rectangle(x + w, y + h, w, h), this->capacity);
			this->southwest = new QuadTree(Rectangle(x - w, y + h, w, h), this->capacity);

			this->divided = true;
		}

		bool insert(Boid *b){
			
			if(!this->boundary.contains(b)){
				return false;
			}

			if(this->boids.size() < this->capacity){
				this->boids.push_back(b);
				return true;

			}else {
				if(!this->divided){
					this->subdivide();
				}

				if(this->northeast->insert(b) || this->northwest->insert(b) || this->southeast->insert(b) || this->southwest->insert(b)){
					return true;
				}

				return false;
			}
		}

		vector<Boid*> query(Rectangle *range){
			vector<Boid*> boids;			

			if(!this->boundary.intersects(range)){
				return boids;
			}else {
				for(int i = 0; i < this->boids.size(); i++){
					if(range->contains(this->boids[i])){
						boids.push_back(this->boids[i]);				
					}
				}

				if(this->divided){
					vector<Boid*> boids_ne = this->northeast->query(range);
					vector<Boid*> boids_nw = this->northwest->query(range);
					vector<Boid*> boids_se = this->southeast->query(range);
					vector<Boid*> boids_sw = this->southwest->query(range);

					boids.insert(boids.end(), boids_ne.begin(), boids_ne.end());
					boids.insert(boids.end(), boids_nw.begin(), boids_nw.end());
					boids.insert(boids.end(), boids_se.begin(), boids_se.end());
					boids.insert(boids.end(), boids_sw.begin(), boids_sw.end());
				}
			}
			
			
			return boids;		
		}

		void show(){
			
			
			glColor3f(0.8, 0.8, 0.8);
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
			glBegin(GL_QUADS);
				glVertex2f(this->boundary.x - this->boundary.w, this->boundary.y - this->boundary.h);
				glVertex2f(this->boundary.x + this->boundary.w, this->boundary.y - this->boundary.h);
				glVertex2f(this->boundary.x + this->boundary.w, this->boundary.y + this->boundary.h);
				glVertex2f(this->boundary.x - this->boundary.w, this->boundary.y + this->boundary.h);
			glEnd();

			if(this->divided){
				this->northeast->show();
				this->northwest->show();
				this->southeast->show();
				this->southwest->show();
			}

		}

		~QuadTree(){
			if(this->divided){
				delete this->northeast;
				delete this->northwest;
				delete this->southeast;
				delete this->southwest;			
			}
		}
};
