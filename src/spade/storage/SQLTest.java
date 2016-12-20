package spade.storage;

import org.apache.jena.atlas.iterator.Iter;
import org.neo4j.cypher.internal.compiler.v2_0.functions.Abs;
import spade.core.Kernel;
import spade.core.AbstractStorage;
import spade.core.AbstractVertex;
import spade.core.AbstractEdge;
import spade.core.Graph;
import spade.core.Vertex;
import spade.core.Edge;
import spade.storage.SQL;

import org.junit.jupiter.api.Test;
import org.junit.runner.RunWith;

import java.util.Iterator;
import java.util.List;
import java.util.Set;

import static org.junit.jupiter.api.Assertions.*;

/**
 * Created by raza on 12/6/16.
 */
class SQLTest {
    private static final SQL testSQLObject = new SQL();
    private static Graph graph = new Graph();


    /**
     * This function executes before any unit test.
     * It creates the environment required to perform the test.
     */
    @org.junit.jupiter.api.BeforeEach
    void setUp()
    {
        // Creating test data to work with.
        // Sample data is taken from the example mentioned in:
        // https://github.com/ashish-gehani/SPADE/wiki/Example%20illustrating%20provenance%20querying

        AbstractVertex v1 = new Vertex();
        v1.removeAnnotation("type");
        v1.addAnnotation("type", "Process");
        v1.addAnnotation("name", "root process");
        v1.addAnnotation("pid", "10");
        v1.addAnnotation("hash", Integer.toString(v1.hashCode()));
        v1.addAnnotation("vertexId", "1");
        graph.putVertex(v1);

        AbstractVertex v2 = new Vertex();
        v2.removeAnnotation("type");
        v2.addAnnotation("type", "Process");
        v2.addAnnotation("name", "child process");
        v2.addAnnotation("pid", "32");
        v2.addAnnotation("hash", Integer.toString(v2.hashCode()));
        v2.addAnnotation("vertexId", "2");
        graph.putVertex(v2);

        AbstractEdge e1 = new Edge(v2, v1);
        e1.removeAnnotation("type");
        e1.addAnnotation("type", "WasTriggeredBy");
        e1.addAnnotation("time", "5:56 PM");
        e1.addAnnotation("hash", Integer.toString(e1.hashCode()));
        e1.addAnnotation("srcVertexHash", v2.getAnnotation("hash"));
        e1.addAnnotation("dstVertexHash", v1.getAnnotation("hash"));
        e1.addAnnotation("edgeId", "1");
        graph.putEdge(e1);

        AbstractVertex v3 = new Vertex();
        v3.removeAnnotation("type");
        v3.addAnnotation("type", "Artifact");
        v3.addAnnotation("filename", "output.tmp");
        v3.addAnnotation("hash", Integer.toString(v3.hashCode()));
        v3.addAnnotation("vertexId", "3");
        graph.putVertex(v3);

        AbstractVertex v4 = new Vertex();
        v4.removeAnnotation("type");
        v4.addAnnotation("type", "Artifact");
        v4.addAnnotation("filename", "output.o");
        v4.addAnnotation("hash", Integer.toString(v4.hashCode()));
        v4.addAnnotation("vertexId", "4");
        graph.putVertex(v4);

        AbstractEdge e2 = new Edge(v2, v3);
        e2.removeAnnotation("type");
        e2.addAnnotation("type", "Used");
        e2.addAnnotation("iotime", "12 ms");
        e2.addAnnotation("hash", Integer.toString(e2.hashCode()));
        e2.addAnnotation("srcVertexHash", v2.getAnnotation("hash"));
        e2.addAnnotation("dstVertexHash", v3.getAnnotation("hash"));
        e2.addAnnotation("edgeId", "2");
        graph.putEdge(e2);

        AbstractEdge e3 = new Edge(v4, v2);
        e3.removeAnnotation("type");
        e3.addAnnotation("type", "WasGeneratedBy");
        e3.addAnnotation("iotime", "11 ms");
        e3.addAnnotation("hash", Integer.toString(e3.hashCode()));
        e3.addAnnotation("srcVertexHash", v4.getAnnotation("hash"));
        e3.addAnnotation("dstVertexHash", v2.getAnnotation("hash"));
        e3.addAnnotation("edgeId", "3");
        graph.putEdge(e3);

        AbstractEdge e4 = new Edge(v4, v3);
        e4.removeAnnotation("type");
        e4.addAnnotation("type", "WasDerivedFrom");
        e4.addAnnotation("hash", Integer.toString(e4.hashCode()));
        e4.addAnnotation("srcVertexHash", v4.getAnnotation("hash"));
        e4.addAnnotation("dstVertexHash", v3.getAnnotation("hash"));
        e4.addAnnotation("edgeId", "4");
        graph.putEdge(e4);

        AbstractVertex v5 = new Vertex();
        v5.removeAnnotation("type");
        v5.addAnnotation("type", "Agent");
        v5.addAnnotation("uid", "10");
        v5.addAnnotation("gid", "10");
        v5.addAnnotation("name", "john");
        v5.addAnnotation("hash", Integer.toString(v5.hashCode()));
        v5.addAnnotation("vertexId", "5");
        graph.putVertex(v5);

        AbstractEdge e5 = new Edge(v1, v5);
        e5.removeAnnotation("type");
        e5.addAnnotation("type", "WasControlledBy");
        e5.addAnnotation("hash", Integer.toString(e5.hashCode()));
        e5.addAnnotation("srcVertexHash", v1.getAnnotation("hash"));
        e5.addAnnotation("dstVertexHash", v5.getAnnotation("hash"));
        e5.addAnnotation("edgeId", "5");
        graph.putEdge(e5);

        AbstractEdge e6 = new Edge(v2, v5);
        e6.removeAnnotation("type");
        e6.addAnnotation("type", "WasControlledBy");
        e6.addAnnotation("hash", Integer.toString(e6.hashCode()));
        e6.addAnnotation("srcVertexHash", v2.getAnnotation("hash"));
        e6.addAnnotation("dstVertexHash", v5.getAnnotation("hash"));
        e6.addAnnotation("edgeId", "6");
        graph.putEdge(e6);

        String connectionString = "default default sa null";
        testSQLObject.initialize(connectionString);

//        SQL.TEST_ENV = true;
//        SQL.TEST_GRAPH = Graph.union(new Graph(), graph);
    }

    /**
     * This function executes after the execution of each unit test.
     * It clears up the environment setup for the test case execution.
     */
    @org.junit.jupiter.api.AfterEach
    void tearDown()
    {
        SQL.TEST_ENV = false;
        SQL.TEST_GRAPH = null;
    }


    /**
     * This function tests the functionality of getAllPaths_new function in spade.storage.SQL.java
     */
    @Test
    void getAllPaths_new()
    {
        //Test Case 1:
        // Creating graph for the expected outcome.
        // The following sample subgraph contains 3 vertices and 3 edges.
        Graph expectedOutcomeCase1 = new Graph();
        int i = 1;
        for(AbstractVertex v: graph.vertexSet())
        {
            if (i == 2 || i == 3 || i == 4)
                expectedOutcomeCase1.putVertex(v);
            i++;
        }
        i = 1;
        for(AbstractEdge e: graph.edgeSet())
        {
            if (i == 2 || i == 3 || i == 4)
                expectedOutcomeCase1.putEdge(e);
            i++;
        }

        Graph actualOutcomeCase1 = testSQLObject.getAllPaths_new(4, 3, 10);
        assertTrue(expectedOutcomeCase1.equals(actualOutcomeCase1));

        // Test Case 2:
        // Creating graph for the expected outcome.
        // The following sample subgraph contains 4 vertices and 4 edges.
        Graph expectedOutcomeCase2 = new Graph();
        i = 1;
        for(AbstractVertex v: graph.vertexSet())
        {
            if(i != 3)
                expectedOutcomeCase2.putVertex(v);
            i++;
        }
        i = 1;
        for(AbstractEdge e: graph.edgeSet())
        {
            if (i != 2 && i != 4)
                expectedOutcomeCase2.putEdge(e);
            i++;
        }

        Graph actualOutcomeCase2 = testSQLObject.getAllPaths_new(4, 5, 10);
        assertTrue(expectedOutcomeCase2.equals(actualOutcomeCase2));

    }

    /*
    * This function tests the functionality of getLineage_new function in spade.storage.SQL.java
    * */
    @Test
    void getLineage_new()
    {
        Graph outcome = testSQLObject.getLineage_new(4, 10, "a", 3);
    }
}