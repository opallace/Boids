class Boid{
	public:
		int perception;
		double maxForce;
		double maxSpeed;

		Vector position;
		Vector velocity;
		Vector acceleration;
		
		Vector t1;
		Vector t2;
		Vector t3;

		Boid(){

			this->perception = p_perception;
			this->maxForce   = p_max_force;
			this->maxSpeed   = p_max_speed;

			this->position.x = rand() % window_width;
			this->position.y = rand() % window_height;
			
			double a = (M_PI * (rand() % 360)) / 180.0;
			this->velocity.x = cos(a);
			this->velocity.y = sin(a);
			
			this->t1.x = 10;
			this->t1.y = 0;
			
			this->t2.x = 0;
			this->t2.y = 3;
			
			this->t3.x = 0;
			this->t3.y = -3;


			this->acceleration;
		}

		void flock(vector<Boid*> boids){
			Vector align      = this->align(boids);
			Vector cohesion   = this->cohesion(boids);
			Vector separation = this->separation(boids);
			
			align.mul(p_align);
			cohesion.mul(p_cohesion);
			separation.mul(p_separation);

			this->acceleration.sum(align);
			this->acceleration.sum(cohesion);
			this->acceleration.sum(separation);
		}

		Vector align(vector<Boid*> boids){
			Vector steering(0, 0);
			int total = 0;

			for(int i = 0; i < boids.size(); i++){
				double d = Vector::distance(this->position, boids[i]->position);
				Vector a = Vector::sub(boids[i]->position, this->position);
				
				if(Vector::angle_between(a, this->velocity) * (180 / M_PI) <= 120 && d > 0){
					steering.sum(boids[i]->velocity);
					total++;
				}
			}

			if(total > 0){
				steering.div((double)total);
				steering.normalize();
				steering.mul(this->maxSpeed);
				steering.sub(this->velocity);
				steering.limit(this->maxForce);
			}
			
			return steering;
		}

		Vector separation(vector<Boid*> boids){
			Vector steering(0, 0);
			int total = 0;

			for(int i = 0; i < boids.size(); i++){
				double d = Vector::distance(this->position, boids[i]->position);
				Vector a = Vector::sub(boids[i]->position, this->position);
				
				if(Vector::angle_between(a, this->velocity) * (180 / M_PI) <= 120 && d > 0){
					Vector diff = Vector::sub(this->position, boids[i]->position);
					diff.normalize();
					diff.div(d);
					steering.sum(diff);
					total++;
				}
			}

			if(total > 0){
				steering.div((double)total);
				steering.normalize();
				steering.mul(this->maxSpeed);
				steering.sub(this->velocity);
				steering.limit(this->maxForce);
			}
			
			return steering;
		}

		Vector cohesion(vector<Boid*> boids){
			Vector steering(0, 0);
			int total = 0;

			for(int i = 0; i < boids.size(); i++){
				double d = Vector::distance(this->position, boids[i]->position);
				Vector a = Vector::sub(boids[i]->position, this->position);
				
				if(Vector::angle_between(a, this->velocity) * (180 / M_PI) <= 120 && d > 0){
					steering.sum(boids[i]->position);
					total++;
				}
			}

			if(total > 0){
				steering.div((double)total);
				steering.sub(this->position);
				steering.normalize();
				steering.mul(this->maxSpeed);
				steering.sub(this->velocity);
				steering.limit(this->maxForce);
			}
			
			return steering;
		}

		void update(){
			this->velocity.sum(this->acceleration);
			this->velocity.limit(this->maxSpeed);
			this->position.sum(this->velocity);
			this->acceleration.mul(0);
		}

		void show(){
			
			
			glPushMatrix();
			
				glTranslatef((float)this->position.x, (float)this->position.y, 0);
				glRotatef(this->velocity.angle() * (180 / M_PI), 0.0f, 0.0f, 1.0f);
				
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				glBegin(GL_TRIANGLES);
					glColor3f(0, 0, 0);
					glVertex2f(this->t1.x, this->t1.y);
					glVertex2f(this->t2.x, this->t2.y);
					glVertex2f(this->t3.x, this->t3.y);
				glEnd();
			glPopMatrix();
		}
};
