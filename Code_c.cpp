//*****************************************__version__2011_7_31_H_9_M_49_***************************************************
//***********************************************alfa___0¡ª¡ª10.1__2011_8_25__ *********************************************************************
#include <stdlib.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <time.h>
#include <math.h>
#include "Code_h.h"
using namespace std;


const int nodenumber = 1000;
const int totaledges = 2000;
const int nets = 500;
const long int playtimes = 100100;
const int sampletimes = 1;
const double w = 10.0;

const double Density = 1.0;
const double alpha = 10.0;

const double delta1 = 0.1;
const double delta2 = 0.1;





void main()
{
	ofstream  out("Frequency.txt");
	ofstream  out1("Record.txt");


	time_t t;
	tm *lt;
	t = time(NULL);
	lt = localtime(&t);
	out << "begin" << '\t' << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec << '\t' << lt->tm_year + 1900 << " " << lt->tm_mon + 1 << " " << lt->tm_mday << endl;
	cout << "begin" << '\t' << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec << '\t' << lt->tm_year + 1900 << " " << lt->tm_mon + 1 << " " << lt->tm_mday << endl;

	cout << "T_fre" << '\t' << "fre_x" << '\t' << "u" << '\t' << "delta" << endl;
	out << "T_fre" << '\t' << "fre_x" << '\t' << "u" << '\t' << "delta" << endl;


	srand(time(0));

	double v, v1, v2, pro, temp, duration1, duration2;
	int i, j, k, focal, partner1, partner2, newpartner1, newpartner2, role, Net_Prior;
	Node *p = NULL;
	Node *q = NULL;
		for (double u = 0; u < 1.000001; u += 0.01)
		{
			double fre = 0;

			for (int h = 0; h < nets; h++)
			{
				list node1[nodenumber];
				list node2[nodenumber];

				int strategy1[nodenumber];
				int strategy2[nodenumber];

				int hstrategy1[nodenumber];
				int hstrategy2[nodenumber];

				double payoffs1[nodenumber];
				double payoffs2[nodenumber];

				double Finalpayoffs[nodenumber];

				int Twine[nodenumber] = { 0 };

				for (k = 0; k<totaledges; k++)
				{
					do
					{
						i = rand()*nodenumber / (RAND_MAX + 1);
						j = rand()*nodenumber / (RAND_MAX + 1);
					} while ((i == j) || (node1[i].check(j) == 1) || (node1[j].check(i) == 1));
					node1[i].insert(j);
					node1[j].insert(i);
				}//generate networks

				for (k = 0; k<totaledges; k++)
				{
					do
					{
						i = rand()*nodenumber / (RAND_MAX + 1);
						j = rand()*nodenumber / (RAND_MAX + 1);
					} while ((i == j) || (node2[i].check(j) == 1) || (node2[j].check(i) == 1));
					node2[i].insert(j);
					node2[j].insert(i);
				}//generate networks

				for (i = 0; i < nodenumber; i++)
				{
					strategy1[i] = rand() % 2;
					strategy2[i] = rand() % 2;

					node1[i].head->nodecode = i;
					node2[i].head->nodecode = i;
				}

				for (i = 0; i < nodenumber*Density; i++)
				{
					do
					{
						j = rand()*nodenumber / (RAND_MAX + 1);
					} while (Twine[j] == 1);
					Twine[j] = 1;
				}

				for (long int mt = 0; mt < playtimes; mt++)///////////////////////////////////////game playing and strategy updating////////////////////////////
				{
					for (i = 0; i < nodenumber; i++)
					{
						payoffs1[i] = 0;
						payoffs2[i] = 0;

						Finalpayoffs[i] = 0;
					}//////////////////////initialize each payoff on each layer/////////////////


					for (i = 0; i < nodenumber; i++)
					{
						partner1 = -1;
						partner2 = -1;
						focal = rand()*nodenumber / (RAND_MAX + 1);
						////////////////////////////////////////////////////////interaction on Net1/////////////////////////////////////////////////////
						if (node1[focal].neinumber() != 0)
						{
							p = node1[focal].head;
							temp = rand() % node1[focal].neinumber();
							for (j = 0; j <= temp; j++)
							{
								p = p->next;
							}
							partner1 = p->nodecode;

							if (strategy1[focal] == 1 && strategy1[partner1] == 1)
							{
								payoffs1[focal] += 1.0;
								payoffs1[partner1] += 1.0;
							}
							if (strategy1[focal] == 0 && strategy1[partner1] == 1)
							{
								payoffs1[focal] += (1.0 + u);
								payoffs1[partner1] += 0;
							}
							if (strategy1[focal] == 1 && strategy1[partner1] == 0)
							{
								payoffs1[focal] += 0;
								payoffs1[partner1] += (1.0 + u);
							}
							if (strategy1[focal] == 0 && strategy1[partner1] == 0)
							{
								payoffs1[focal] += u;
								payoffs1[partner1] += u;
							}
						}
						////////////////////////////////////////////////////////interaction on Net1/////////////////////////////////////////////////////

						////////////////////////////////////////////////////////interaction on Net2/////////////////////////////////////////////////////
						if (node2[focal].neinumber() != 0)
						{
							p = node2[focal].head;
							temp = rand() % node2[focal].neinumber();
							for (j = 0; j <= temp; j++)
							{
								p = p->next;
							}
							partner2 = p->nodecode;

							if (strategy2[focal] == 1 && strategy2[partner2] == 1)
							{
								payoffs2[focal] += 1.0;
								payoffs2[partner2] += 1.0;
							}
							if (strategy2[focal] == 0 && strategy2[partner2] == 1)
							{
								payoffs2[focal] += (1.0 + u);
								payoffs2[partner2] += 0;
							}
							if (strategy2[focal] == 1 && strategy2[partner2] == 0)
							{
								payoffs2[focal] += 0;
								payoffs2[partner2] += (1.0 + u);
							}
							if (strategy2[focal] == 0 && strategy2[partner2] == 0)
							{
								payoffs2[focal] += u;
								payoffs2[partner2] += u;
							}
						}
						////////////////////////////////////////////////////////interaction on Net2/////////////////////////////////////////////////////

						if (partner1 == -1 && partner2 == -1)
						{
							continue;
						}

						if (partner1 != -1 && partner2 == -1)
						{
							p = node1[focal].head;
							while (p != NULL)
							{
								if (p->nodecode == partner1)
								{
									p->age = p->age + delta1 * pow(-1, strategy1[partner1] + 1);

									if (p->age > MAXAGE)
									{
										p->age = MAXAGE;
									}
									if (p->age < MINAGE)
									{
										p->age = MINAGE;
									}
									break;
								}
								p = p->next;
							}////////////////////adjust focal's value for linkage in a coevolved way///////////////////////////////

							p = node1[partner1].head;
							while (p != NULL)
							{
								if (p->nodecode == focal)
								{
									p->age = p->age + delta1 * pow(-1, strategy1[focal] + 1);

									if (p->age > MAXAGE)
									{
										p->age = MAXAGE;
									}
									if (p->age < MINAGE)
									{
										p->age = MINAGE;
									}
									break;
								}
								p = p->next;
							}

							p = node1[focal].head;
							while (p != NULL)
							{
								if (p->nodecode == partner1)
								{
									break;
								}
								p = p->next;
							}
							pro = (double)rand() / RAND_MAX;
							if (pro < 1.0 - p->age)
							{
								node1[focal].cutoff(partner1);
								node1[partner1].cutoff(focal);

								do
								{
									newpartner1 = rand()*nodenumber / (RAND_MAX + 1);
								} while (node1[focal].check(newpartner1) == 1 || node1[newpartner1].check(focal) == 1 || newpartner1 == focal || newpartner1 == partner1);
								node1[focal].insert(newpartner1);
								node1[newpartner1].insert(focal);
							}
							continue;
						}

						if (partner1 == -1 && partner2 != -1)
						{
							p = node2[focal].head;
							while (p != NULL)
							{
								if (p->nodecode == partner2)
								{
									p->age = p->age + delta2 * pow(-1, strategy2[partner2] + 1);

									if (p->age > MAXAGE)
									{
										p->age = MAXAGE;
									}
									if (p->age < MINAGE)
									{
										p->age = MINAGE;
									}
									break;
								}
								p = p->next;
							}

							p = node2[partner2].head;
							while (p != NULL)
							{
								if (p->nodecode == focal)
								{
									p->age = p->age + delta2 * pow(-1, strategy2[focal] + 1);

									if (p->age > MAXAGE)
									{
										p->age = MAXAGE;
									}
									if (p->age < MINAGE)
									{
										p->age = MINAGE;
									}
									break;
								}
								p = p->next;
							}

							p = node2[focal].head;
							while (p != NULL)
							{
								if (p->nodecode == partner2)
								{
									break;
								}
								p = p->next;
							}
							pro = (double)rand() / RAND_MAX;
							if (pro < 1.0 - p->age)
							{
								node2[focal].cutoff(partner2);
								node2[partner2].cutoff(focal);

								do
								{
									newpartner2 = rand()*nodenumber / (RAND_MAX + 1);
								} while (node2[focal].check(newpartner2) == 1 || node2[newpartner2].check(focal) == 1 || newpartner2 == focal || newpartner2 == partner2);
								node2[focal].insert(newpartner2);
								node2[newpartner2].insert(focal);
							}
							continue;
						}


//--------------------------------------------------------- duration adjusting on both netowrks where both coordinated and uncoordinated duration adjustment may occur----------------------------
						if(partner1 != -1 && partner2 != -1)
						{
							if(Twine[focal] == 1)
							{
								p = node1[focal].head;
								while (p != NULL)
								{
									if (p->nodecode == partner1)
									{
										pro = (double)rand() / RAND_MAX;
									
										temp = 1.0 / (1.0 + exp(alpha*(payoffs1[focal] - payoffs2[focal])));
										if(pro < temp)
										{
											p->age = p->age + delta1 * pow(-1, strategy1[partner1] + 1) - delta2 * temp;
										}
										else
										{
											p->age = p->age + delta1 * pow(-1, strategy1[partner1] + 1) + delta2 * temp;
										}

										if (p->age > MAXAGE)
										{
											p->age = MAXAGE;
										}
										if (p->age < MINAGE)
										{
											p->age = MINAGE;
										}
										break;
									}
									p = p->next;
								}
							}
							else
							{
								p = node1[focal].head;
								while (p != NULL)
								{
									if (p->nodecode == partner1)
									{
										p->age = p->age + delta1 * pow(-1, strategy1[partner1] + 1);

										if (p->age > MAXAGE)
										{
											p->age = MAXAGE;
										}
										if (p->age < MINAGE)
										{
											p->age = MINAGE;
										}
										break;
									}
									p = p->next;
								}
							}


							if(Twine[partner1] == 1)
							{
								p = node1[partner1].head;
								while (p != NULL)
								{
									if (p->nodecode == focal)
									{
										pro = (double)rand() / RAND_MAX;

										temp = 1.0 / (1.0 + exp(alpha*(payoffs1[partner1] - payoffs2[partner1])));
										if (pro < temp)
										{
											p->age = p->age + delta1 * pow(-1, strategy1[focal] + 1) - delta2 * temp;
										}
										else
										{
											p->age = p->age + delta1 * pow(-1, strategy1[focal] + 1) + delta2 * temp;
										}

										if (p->age > MAXAGE)
										{
											p->age = MAXAGE;
										}
										if (p->age < MINAGE)
										{
											p->age = MINAGE;
										}
										break;
									}
									p = p->next;
								}
							}
							else
							{
								p = node1[partner1].head;
								while (p != NULL)
								{
									if (p->nodecode == focal)
									{
										p->age = p->age + delta1 * pow(-1, strategy1[focal] + 1);

										if (p->age > MAXAGE)
										{
											p->age = MAXAGE;
										}
										if (p->age < MINAGE)
										{
											p->age = MINAGE;
										}
										break;
									}
									p = p->next;
								}
							}


							if(Twine[focal] == 1)
							{
								p = node2[focal].head;
								while (p != NULL)
								{
									if (p->nodecode == partner2)
									{
										pro = (double)rand() / RAND_MAX;
									
										temp = 1.0 / (1.0 + exp(alpha*(payoffs2[focal] - payoffs1[focal])));
										if(pro < temp)
										{
											p->age = p->age + delta2 * pow(-1, strategy2[partner2] + 1) - delta1 * temp;
										}
										else
										{
											p->age = p->age + delta2 * pow(-1, strategy2[partner2] + 1) + delta1 * temp;
										}

										if (p->age > MAXAGE)
										{
											p->age = MAXAGE;
										}
										if (p->age < MINAGE)
										{
											p->age = MINAGE;
										}
										break;
									}
									p = p->next;
								}
							}
							else
							{
								p = node2[focal].head;
								while (p != NULL)
								{
									if (p->nodecode == partner2)
									{
										p->age = p->age + delta2 * pow(-1, strategy2[partner2] + 1);

										if (p->age > MAXAGE)
										{
											p->age = MAXAGE;
										}
										if (p->age < MINAGE)
										{
											p->age = MINAGE;
										}
										break;
									}
									p = p->next;
								}
							}


							if(Twine[partner2] == 1)
							{
								p = node2[partner2].head;
								while (p != NULL)
								{
									if (p->nodecode == focal)
									{
										pro = (double)rand() / RAND_MAX;

										temp = 1.0 / (1.0 + exp(alpha*(payoffs2[partner2] - payoffs1[partner2])));
										if (pro < temp)
										{
											p->age = p->age + delta2 * pow(-1, strategy2[focal] + 1) - delta1 * temp;
										}
										else
										{
											p->age = p->age + delta2 * pow(-1, strategy2[focal] + 1) + delta1 * temp;
										}

										if (p->age > MAXAGE)
										{
											p->age = MAXAGE;
										}
										if (p->age < MINAGE)
										{
											p->age = MINAGE;
										}
										break;
									}
									p = p->next;
								}
							}
							else
							{
								p = node2[partner2].head;
								while (p != NULL)
								{
									if (p->nodecode == focal)
									{
										p->age = p->age + delta2 * pow(-1, strategy2[focal] + 1);

										if (p->age > MAXAGE)
										{
											p->age = MAXAGE;
										}
										if (p->age < MINAGE)
										{
											p->age = MINAGE;
										}
										break;
									}
									p = p->next;
								}
							}
						}

						
//------------------------------------------ Linking Dynamics on both networks where both coordinated and uncoordinated linking dynamics may occur ------------------------------------------
						if (partner1 != -1 && partner2 != -1)
						{
							if (node2[focal].check(partner1) == 1)
							{
								p = node1[focal].head;
								while (p != NULL)
								{
									if (p->nodecode == partner1)
									{
										break;
									}
									p = p->next;
								}

								q = node2[focal].head;
								while (q != NULL)
								{
									if (q->nodecode == partner1)
									{
										break;
									}
									q = q->next;
								}

								duration1 = 0.5 * (p->age + q->age);

								if (duration1 > MAXAGE)
								{
									duration1 = MAXAGE;
								}
								if (duration1 < MINAGE)
								{
									duration1 = MINAGE;
								}
							}

							else
							{
								p = node1[focal].head;
								while (p != NULL)
								{
									if (p->nodecode == partner1)
									{
										break;
									}
									p = p->next;
								}
								duration1 = p->age;

								if (duration1 > MAXAGE)
								{
									duration1 = MAXAGE;
								}
								if (duration1 < MINAGE)
								{
									duration1 = MINAGE;
								}
							}

							if (node1[focal].check(partner2) == 1)
							{
								p = node2[focal].head;
								while (p != NULL)
								{
									if (p->nodecode == partner2)
									{
										break;
									}
									p = p->next;
								}

								q = node1[focal].head;
								while (q != NULL)
								{
									if (q->nodecode == partner2)
									{
										break;
									}
									q = q->next;
								}

								duration2 = 0.5 * (p->age + q->age);

								if (duration2 > MAXAGE)
								{
									duration2 = MAXAGE;
								}
								if (duration2 < MINAGE)
								{
									duration2 = MINAGE;
								}
							}
							else
							{
								p = node2[focal].head;
								while (p != NULL)
								{
									if (p->nodecode == partner2)
									{
										break;
									}
									p = p->next;
								}
								duration2 = p->age;

								if (duration2 > MAXAGE)
								{
									duration2 = MAXAGE;
								}
								if (duration2 < MINAGE)
								{
									duration2 = MINAGE;
								}
							}


							Net_Prior = rand() % 2 + 1;

							if (Net_Prior == 1)
							{
								pro = (double)rand() / RAND_MAX;
								if (pro < 1.0 - duration1)
								{
									node1[focal].cutoff(partner1);
									node1[partner1].cutoff(focal);

									do
									{
										newpartner1 = rand()*nodenumber / (RAND_MAX + 1);
									} while (node1[focal].check(newpartner1) == 1 || node1[newpartner1].check(focal) == 1 || newpartner1 == focal || newpartner1 == partner1);
									node1[focal].insert(newpartner1);
									node1[newpartner1].insert(focal);

									if (node2[focal].check(partner1) == 1)
									{
										node2[focal].cutoff(partner1);
										node2[partner1].cutoff(focal);

										do
										{
											newpartner2 = rand()*nodenumber / (RAND_MAX + 1);
										} while (node2[focal].check(newpartner2) == 1 || node2[newpartner2].check(focal) == 1 || newpartner2 == focal || newpartner2 == partner1);
										node2[focal].insert(newpartner2);
										node2[newpartner2].insert(focal);
									}
								}

								pro = (double)rand() / RAND_MAX;
								if (pro < 1.0 - duration2)
								{
									int flag;
									node2[focal].cutoff(partner2);
									flag = node2[partner2].cutoff(focal);

									if (flag)
									{
										do
										{
											newpartner2 = rand()*nodenumber / (RAND_MAX + 1);
										} while (node2[focal].check(newpartner2) == 1 || node2[newpartner2].check(focal) == 1 || newpartner2 == focal || newpartner2 == partner2);
										node2[focal].insert(newpartner2);
										node2[newpartner2].insert(focal);

										if (node1[focal].check(partner2) == 1)
										{
											node1[focal].cutoff(partner2);
											node1[partner2].cutoff(focal);

											do
											{
												newpartner1 = rand()*nodenumber / (RAND_MAX + 1);
											} while (node1[focal].check(newpartner1) == 1 || node1[newpartner1].check(focal) == 1 || newpartner1 == focal || newpartner1 == partner2);
											node1[focal].insert(newpartner1);
											node1[newpartner1].insert(focal);
										}
									}			
								}
							}


							if (Net_Prior == 2)
							{
								pro = (double)rand() / RAND_MAX;
								if (pro < 1.0 - duration2)
								{
									node2[focal].cutoff(partner2);
									node2[partner2].cutoff(focal);

									do
									{
										newpartner2 = rand()*nodenumber / (RAND_MAX + 1);
									} while (node2[focal].check(newpartner2) == 1 || node2[newpartner2].check(focal) == 1 || newpartner2 == focal || newpartner2 == partner2);
									node2[focal].insert(newpartner2);
									node2[newpartner2].insert(focal);
								}

								if (node1[focal].check(partner2) == 1)
								{
									node1[focal].cutoff(partner2);
									node1[partner2].cutoff(focal);

									do
									{
										newpartner1 = rand()*nodenumber / (RAND_MAX + 1);
									} while (node1[focal].check(newpartner1) == 1 || node1[newpartner1].check(focal) == 1 || newpartner1 == focal || newpartner1 == partner2);
									node1[focal].insert(newpartner1);
									node1[newpartner1].insert(focal);
								} 

								pro = (double)rand() / RAND_MAX;
								if (pro < 1.0 - duration1)
								{
									int flag;
									node1[focal].cutoff(partner1);
									flag = node1[partner1].cutoff(focal);

									if (flag)
									{
										do
										{
											newpartner1 = rand()*nodenumber / (RAND_MAX + 1);
										} while (node1[focal].check(newpartner1) == 1 || node1[newpartner1].check(focal) == 1 || newpartner1 == focal || newpartner1 == partner1);
										node1[focal].insert(newpartner1);
										node1[newpartner1].insert(focal);

										if (node2[focal].check(partner1) == 1)
										{
											node2[focal].cutoff(partner1);
											node2[partner1].cutoff(focal);

											do
											{
												newpartner2 = rand()*nodenumber / (RAND_MAX + 1);
											} while (node2[focal].check(newpartner2) == 1 || node2[newpartner2].check(focal) == 1 || newpartner2 == focal || newpartner2 == partner1);
											node2[focal].insert(newpartner2);
											node2[newpartner2].insert(focal);
										}
									}
								}
							}
						}
					}//end of i ------------ each agent averagely lauches one game and adjusts social ties


					for (i = 0; i < nodenumber; i++)
					{
						hstrategy1[i] = strategy1[i];
						hstrategy2[i] = strategy2[i];

						Finalpayoffs[i] = 0.5 * (payoffs1[i] + payoffs2[i]);
					}////////////////////////reshape final payoffs and copy strategy/////////////////////////////////////


					for (i = 0; i < nodenumber; i++)
					{
						////////////////////////////////////////////////strategy updating on Net1////////////////////////////////////////////
						if (node1[i].neinumber() == 0)
						{
							continue;
						}
						p = node1[i].head;
						role = rand() % node1[i].neinumber();
						for (j = 0; j <= role; j++)
						{
							p = p->next;
						}
						role = p->nodecode;

						pro = (double)rand() / RAND_MAX;
						if (pro < 1.0 / (1.0 + exp(w*(Finalpayoffs[i] - Finalpayoffs[role]))))
						{
							strategy1[i] = hstrategy1[role];
						}
					}
					////////////////////////////////////////////////strategy updating on Net1////////////////////////////////////////////

					////////////////////////////////////////////////strategy updating on Net2////////////////////////////////////////////
					for (i = 0; i < nodenumber; i++)
					{
						if (node2[i].neinumber() == 0)
						{
							continue;
						}
						p = node2[i].head;
						role = rand() % node2[i].neinumber();
						for (j = 0; j <= role; j++)
						{
							p = p->next;
						}
						role = p->nodecode;

						pro = (double)rand() / RAND_MAX;
						if (pro < 1.0 / (1.0 + exp(w*(Finalpayoffs[i] - Finalpayoffs[role]))))
						{
							strategy2[i] = hstrategy2[role];
						}
					}////////////////////updating strategy of each agent/////////////////////


					if (mt <= 5000 || mt % 1000 == 0)
					{
						////////////////////////////////counting fraction of Net1////////////////////////////////					
						v1 = 0;
						for (k = 0; k < nodenumber; k++)

						{
							if (strategy1[k] == 1)
							{
								v1 += 1.0;
							}
						}
						v1 /= nodenumber;
						////////////////////////////////counting fraction of Net1////////////////////////////////

						////////////////////////////////counting fraction of Net2////////////////////////////////
						v2 = 0;
						for (k = 0; k < nodenumber; k++)

						{
							if (strategy2[k] == 1)
							{
								v2 += 1.0;
							}
						}
						v2 /= nodenumber;
						////////////////////////////////counting fraction of Net2////////////////////////////////

						if (v1 == 1 && v2 == 1)
						{
							v = (v1 + v2) / 2;
							fre += v * sampletimes;
							t = time(NULL);
							lt = localtime(&t);

							out1 << "ahead" << '\t' << mt << '\t' << h << '\t' << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec << endl;
							out1 << v << '\t' << v1 << '\t' << v2 << endl;
							break;
						}
						if (v1 == 1 && v2 == 0)
						{
							v = (v1 + v2) / 2;
							fre += v * sampletimes;
							t = time(NULL);
							lt = localtime(&t);

							out1 << "ahead" << '\t' << mt << '\t' << h << '\t' << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec << endl;
							out1 << v << '\t' << v1 << '\t' << v2 << endl;
							break;
						}
						if (v1 == 0 && v2 == 1)
						{
							v = (v1 + v2) / 2;
							fre += v * sampletimes;
							t = time(NULL);
							lt = localtime(&t);

							out1 << "ahead" << '\t' << mt << '\t' << h << '\t' << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec << endl;
							out1 << v << '\t' << v1 << '\t' << v2 << endl;
							break;
						}
						if (v1 == 0 && v2 == 0)
						{
							v = (v1 + v2) / 2;
							fre += v * sampletimes;
							t = time(NULL);
							lt = localtime(&t);

							out1 << "ahead" << '\t' << mt << '\t' << h << '\t' << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec << endl;
							out1 << v << '\t' << v1 << '\t' << v2 << endl;
							break;
						}
					}//////////////////ahead testing



					if (mt >= playtimes - sampletimes)//////////calculate the means of offer level and acceptance level
					{
						out1 << "end" << '\t' << h << '\t';
						v1 = 0;
						for (k = 0; k < nodenumber; k++)

						{
							if (strategy1[k] == 1)
							{
								v1 += 1.0;
							}
						}
						v1 /= nodenumber;


						v2 = 0;
						for (k = 0; k < nodenumber; k++)

						{
							if (strategy2[k] == 1)
							{
								v2 += 1.0;
							}
						}
						v2 /= nodenumber;

						v = (v1 + v2) / 2;
						fre += v;
						out1 << v << endl;
					}
				}//////end of mt
			}/////end of h
			fre /= (nets * sampletimes);


			cout << fre << '\t' << u << '\t' << delta1 << '\t' << Density << '\t' << alpha << endl;
			out << u << '\t' << fre << '\t' << delta1 << '\t' << Density << '\t' << alpha << endl;

			if (fre == 0)
			{
				break;
			}
		}//end of u
	t = time(NULL);
	lt = localtime(&t);
	cout << "end" << '\t' << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec << endl;
	out << "end" << '\t' << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec << endl;
}//end main